#include <cimc/cimc.h>
#include <CimClientLib/cmci.h>
#include <CimClientLib/native.h>
#include <unistd.h>

extern char *value2Chars(CIMCType type, CIMCValue * value);

void showObjectPath( CIMCObjectPath * objectpath );
void showInstance( CIMCInstance *instance );
void showClass( CIMCClass *in_class );
void showProperty( CIMCData data, char *name );
