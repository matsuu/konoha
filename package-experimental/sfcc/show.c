#include <cimc/cimc.h>
#include <CimClientLib/cmci.h>
#include <CimClientLib/native.h>
#include <unistd.h>
#include <string.h>

#include "show.h"

void showObjectPath( CIMCObjectPath * objectpath )
{
  CIMCString * namespace = objectpath->ft->getNameSpace(objectpath, NULL);
  CIMCString * classname = objectpath->ft->getClassName(objectpath, NULL);
  int numkeys = objectpath->ft->getKeyCount(objectpath, NULL);
  int i;
  char *cv;
  
  if (namespace && namespace->hdl)
    {
      printf("namespace=%s\n", (char *)namespace->hdl);
    }
  
  if (classname && classname->hdl)
    {
      printf("classname=%s\n", (char *)classname->hdl);
    }
  
  if (numkeys)
    {
      printf("keys:\n");
      for (i=0; i<numkeys; i++)
	{
	  CIMCString * keyname;
	  CIMCData data = objectpath->ft->getKeyAt(objectpath, i,
						   &keyname, NULL);
	  printf("\t%s=%s\n", (char *)keyname->hdl,
		 cv=value2Chars(data.type, &data.value));
	  if(cv) free(cv);
	  if(keyname) CMRelease(keyname);
	}
    }
  
  if (classname) CMRelease(classname);
  if (namespace) CMRelease(namespace);
}

static char *CIMCState_str(CIMCValueState state)
{
  char *retval;
  
  switch (state) {
  case CIMC_goodValue:
    retval = "CIMC_goodValue";
    break;
    
  case CIMC_nullValue:
    retval = "CIMC_nullValue";
    break;
    
  case CIMC_keyValue:
    retval = "CIMC_keyValue";
    break;
    
  case CIMC_notFound:
    retval = "CIMC_notFound";
    break;
    
  case CIMC_badValue:
    retval = "CIMC_badValue";
    break;
    
  default:
    retval = "!Unknown CIMCValueState!";
    break;
  }
  
  return retval;
}

void showProperty( CIMCData data, char *name )
{
  char *valuestr;
  CIMCValueState state = data.state & ~CIMC_keyValue;
  if (state == CIMC_goodValue)
    {
      if (CMIsArray(data))
	{
	  CIMCArray *arr   = data.value.array;
	  CIMCType  eletyp = data.type & ~CIMC_ARRAY;
	  int j, n;
	  n = CMGetArrayCount(arr, NULL);
	  for (j = 0; j < n; ++j)
	    {
	      CIMCData ele = CMGetArrayElementAt(arr, j, NULL);
	      valuestr = value2Chars(eletyp, &ele.value);
	      printf("\t%s[%d]=%s\n", name, j, valuestr);
	      free (valuestr);
	    }
	}
      else
	{
	  if (state == CIMC_goodValue)
	    {
	      valuestr = value2Chars(data.type, &data.value);
	      printf("\t%s=%s\n", name, valuestr);
	      free (valuestr);
	    }
	}
    }
  else
    {
      printf("\t%s=%d(%s)\n", name, data.state, CIMCState_str(data.state));
    }
}

void showInstance( CIMCInstance *instance )
{
  CIMCObjectPath * objectpath = instance->ft->getObjectPath(instance, NULL);
  CIMCString * objectpathname = objectpath->ft->toString(objectpath, NULL);
  CIMCString * namespace = objectpath->ft->getNameSpace(objectpath, NULL);
  CIMCString * classname = objectpath->ft->getClassName(objectpath, NULL);
  int numkeys = objectpath->ft->getKeyCount(objectpath, NULL);
  int numproperties = instance->ft->getPropertyCount(instance, NULL);
  int i;
  
  if (objectpathname && objectpathname->hdl)
    {
      printf("objectpath=%s\n", (char *)objectpathname->hdl);
    }
  
  if (namespace && namespace->hdl)
    {
      printf("namespace=%s\n", (char *)namespace->hdl);
    }
  
  if (classname && classname->hdl)
    {
      printf("classname=%s\n", (char *)classname->hdl);
    }
  
  if (numkeys)
    {
      printf("keys:\n");
      for (i=0; i<numkeys; i++)
	{
	  CIMCString * keyname;
	  CIMCData data = objectpath->ft->getKeyAt(objectpath, i,
						   &keyname, NULL);
	  char *ptr=NULL;
	  printf("\t%s=%s\n", (char *)keyname->hdl,
		 (ptr=value2Chars(data.type, &data.value)));
	  free(ptr);
	  if (keyname) CMRelease(keyname);
	}
    }
  else
    {
      printf("No keys!\n");
    }
  
  if (numproperties)
    {
      printf("properties:\n");
      for (i=0; i<numproperties; i++)
	{
	  CIMCString * propertyname;
	  CIMCData data = instance->ft->getPropertyAt(instance, i,
						      &propertyname, NULL);
	  showProperty( data, (char *)propertyname->hdl );
	  CMRelease(propertyname);
	}
    }
  else
    {
      printf("No properties!\n");
    }
  
  if (classname) CMRelease(classname);
  if (namespace) CMRelease(namespace);
  if (objectpathname) CMRelease(objectpathname);
  if (objectpath) CMRelease(objectpath);
}


void showClass( CIMCClass * class )
{
  CIMCString * classname = class->ft->getClassName(class, NULL);
  int numproperties = class->ft->getPropertyCount(class, NULL);
  int i;
  char *cv;
  
  if (classname && classname->hdl)
    {
      printf("classname=%s\n", (char *)classname->hdl);
    }
  
  if (numproperties)
    {
      printf("properties:\n");
      for (i=0; i<numproperties; i++)
	{
   	  CIMCString * propertyname;
   	  CIMCData data = class->ft->getPropertyAt(class, i,
   						   &propertyname, NULL);
   	  if (propertyname) {
   	    CIMCData data = class->ft->getPropQualifier(class,(char *)propertyname->hdl,"KEY",NULL);
   	    if (data.state != CIMC_nullValue && data.value.boolean) {
   	      printf ("[KEY]");
   	    }
   	  }
   	  if (data.state==0)
	    {
   	      printf("\t%s=%s\n", (char *)propertyname->hdl,
   		     cv=value2Chars(data.type, &data.value));
   	      if(cv) free(cv);
   	    }
   	  else printf("\t%s=NIL\n", (char *)propertyname->hdl);
   	  if (propertyname) {
   	    CMRelease(propertyname);
   	  }
   	}
    }
  
  if (classname) CMRelease(classname);
}
