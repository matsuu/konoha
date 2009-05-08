#import <Appkit/Appkit.h>
#include <konoha.h>

//start Convert NSString
NSString *KString_toNSString(String *string)
{
	char *line = knh_String_tochar(string);
	return [[NSString alloc] initWithUTF8String: line];
}
//end Convert NSString

//start NSAutoreleasePool 
METHOD NSAutoreleasePool_new(Ctx *ctx, knh_sfp_t *sfp)
{
	NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
	knh_Glue_t *glue = sfp[0].glue;
	glue->ptr = (void*)pool;
	KNH_RETURN(ctx, sfp, sfp[0].o);
}

METHOD NSAutoreleasePool_drain(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_Glue_t *glue = sfp[0].glue;
	NSAutoreleasePool *pool = (NSAutoreleasePool *)glue->ptr;
	[pool drain];
	KNH_RETURN_void(ctx, sfp);
}
//end NSAutoreleasePool

//start NSApplication
METHOD NSApplication_new(Ctx *ctx, knh_sfp_t *sfp)
{
	NSApplication *App = [NSApplication sharedApplication];
	knh_Glue_t *glue = sfp[0].glue;
	glue->ptr = (void*)App;
	KNH_RETURN(ctx, sfp, sfp[0].o);
}
METHOD NSApplication_run(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_Glue_t *glue = sfp[0].glue;
	NSApplication *NSApp = (NSApplication *)glue->ptr;
	[NSApp run];
	KNH_RETURN_void(ctx, sfp);
}
//end NSApplication

//start NSSound
METHOD NSSound_new(Ctx *ctx, knh_sfp_t *sfp)
{
	NSSound *sound = [NSSound alloc];
	knh_Glue_t *glue = sfp[0].glue;
	glue->ptr = (void*)sound;
	KNH_RETURN(ctx,sfp,sfp[0].o);
}
METHOD NSSound_play(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_Glue_t *glue = sfp[0].glue;
	NSSound *sound = (NSSound *)glue->ptr;
	[sound play];
	KNH_RETURN_void(ctx,sfp);
}
METHOD NSSound_initWithContentsOfFile(Ctx *ctx,knh_sfp_t *sfp)
{
	knh_Glue_t *glue = sfp[0].glue;
	NSString *filepath = KString_toNSString(sfp[1].s);
	//	boolean byRef = ???;
	NSSound *sound = (NSSound*)glue->ptr;
	[sound initWithContentsOfFile:filepath byReference:NO];
	KNH_RETURN_void(ctx,sfp);
}
//end NSSound

//start NSView
METHOD NSView_new(Ctx *ctx, knh_sfp_t *sfp)
{
	NSView *view = [NSView alloc];
	knh_Glue_t *glue = sfp[0].glue;
	glue->ptr = (void*)view;
	KNH_RETURN(ctx,sfp,sfp[0].o);
}
METHOD NSView_initWithFrame(Ctx *ctx, knh_sfp_t *sfp)
{
	float x = p_float(sfp[1]);
	float y = p_float(sfp[2]);
	float w = p_float(sfp[3]);
	float h = p_float(sfp[4]);
	NSRect rect = NSMakeRect(x,y,w,h);
	knh_Glue_t *glue = sfp[0].glue;
	NSView *view = (NSView*)glue->ptr;
	[view initWithFrame:rect];
	KNH_RETURN_void(ctx, sfp);
}
METHOD NSView_addSubview(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_Glue_t *glue = sfp[0].glue;
	NSView *view = (NSView*)glue->ptr;
//	NSView *view2 = (NSView*)glue->ptr[1];
//	NSView *view2 = (NSView*)sfp[1].glue->ptr;
	glue = sfp[1].glue;
	NSButton *button  = (NSButton*)glue->ptr;
	[view addSubview:button];
	KNH_RETURN_void(ctx, sfp);
}
//end NSView


//start NSWindow
METHOD NSWindow_new(Ctx *ctx, knh_sfp_t* sfp)
{
	NSWindow *win = [NSWindow alloc];
	knh_Glue_t *glue = sfp[0].glue;
	glue->ptr = (void*)win;
	KNH_RETURN(ctx, sfp, sfp[0].o);
}
METHOD NSWindow_initWithContentRect(Ctx *ctx, knh_sfp_t *sfp)
{
	float x = p_float(sfp[1]);
	float y = p_float(sfp[2]);
	float w = p_float(sfp[3]);
	float h = p_float(sfp[4]);
	NSRect rect = NSMakeRect(x,y,w,h);
	knh_Glue_t *glue = sfp[0].glue;
	NSWindow *win = (NSWindow*)glue->ptr;
	[win initWithContentRect:rect styleMask:15 backing:2 defer:0];
	KNH_RETURN_void(ctx, sfp);
}
METHOD NSWindow_setTitle(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_Glue_t *glue = sfp[0].glue;
	NSWindow *win = (NSWindow*)glue->ptr;
	NSString *title = KString_toNSString(sfp[1].s);
	[win setTitle:title];
	KNH_RETURN_void(ctx, sfp);
}
METHOD NSWindow_contentView(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_Glue_t *glue = sfp[0].glue;
	NSWindow *win = (NSWindow*)glue->ptr;
 	NSView *view = [win contentView];
	knh_Glue_t *ret = (knh_Glue_t *)new_Glue(ctx, "This",NULL, NULL);
	ret->ptr = (void *)view;
	KNH_RETURN(ctx, sfp, ret);
}
METHOD NSWindow_orderFrontRegardless(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_Glue_t *glue = sfp[0].glue;
	NSWindow *win = (NSWindow*)(glue->ptr);
	[win orderFrontRegardless];
	KNH_RETURN_void(ctx, sfp);
}
METHOD NSWindow_initWithContentRect_styleMask_backing_defer(Ctx* ctx, knh_sfp_t *sfp)
{
	knh_Glue_t *glue = sfp[0].glue;
	NSWindow *win =(NSWindow*)glue->ptr;
	return ;
}
METHOD NSWindow_display(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_Glue_t *glue = sfp[0].glue;
	NSWindow *win = (NSWindow *)glue->ptr;
	[win display];
	KNH_RETURN_void(ctx, sfp);
}
METHOD NSWindow_setLevel(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_Glue_t *glue = sfp[0].glue;
	NSWindow *win = (NSWindow *)glue->ptr;
	int a = p_int(sfp[1]);
	[win setLevel:a];
}
METHOD NSWindow_center(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_Glue_t *glue = sfp[0].glue;
	NSWindow *win = (NSWindow *)glue->ptr;
	[win center];
	KNH_RETURN_void(ctx,sfp);
}
METHOD NSWindow_becomeKeyWindow(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_Glue_t *glue = sfp[0].glue;
	NSWindow *win = (NSWindow *)glue->ptr;
	[win becomeKeyWindow];
	KNH_RETURN_void(ctx,sfp);
}
METHOD NSWindow_setBackgroundColor(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_Glue_t *glue = sfp[0].glue;
	NSWindow *win = (NSWindow *)glue->ptr;
	glue = sfp[1].glue;
	NSColor *color = (NSColor *)glue->ptr;
	[win setBackgroundColor:color];
	KNH_RETURN_void(ctx,sfp);
}
//end NSWindow


//start NSRect
METHOD NSRect_new(Ctx *ctx, knh_sfp_t* sfp)
{
	NSWindow *win = [NSWindow alloc];
	knh_Glue_t *glue = sfp[0].glue;
	glue->ptr = (void*)win;
	KNH_RETURN(ctx, sfp, sfp[0].o);
}
//end NSRect


//start NSButton
METHOD NSButton_new(Ctx *ctx,knh_sfp_t* sfp)
{
	NSButton *button = [NSButton alloc];
	knh_Glue_t *glue = sfp[0].glue;
	glue->ptr = (void*)button;
	KNH_RETURN(ctx, sfp, sfp[0].o);
}
METHOD NSButton_initWithFrame(Ctx *ctx, knh_sfp_t *sfp)
{
	float x = p_float(sfp[1]);
	float y = p_float(sfp[2]);
	float w = p_float(sfp[3]);
	float h = p_float(sfp[4]);
	NSRect rect = NSMakeRect(x,y,w,h);
	knh_Glue_t *glue = sfp[0].glue;
	NSButton *button = (NSButton*)glue->ptr;
	[button initWithFrame:rect];

	KNH_RETURN_void(ctx,sfp);
}
//ent NSButton

//start NSBox 
METHOD NSBox_new(Ctx *ctx, knh_sfp_t *sfp)
{
	NSBox *pool = [[NSBox alloc] init];
	knh_Glue_t *glue = sfp[0].glue;
	glue->ptr = (void*)pool;
	KNH_RETURN(ctx, sfp, sfp[0].o);
}

//end NSBox

//start NSColor
METHOD NSColor_new(Ctx *ctx,knh_sfp_t *sfp)
{
	NSColor *color = [NSColor alloc];
	knh_Glue_t *glue = sfp[0].glue;
	glue->ptr = (void*)color;
	KNH_RETURN(ctx, sfp, sfp[0].o);
}
METHOD NSColor_colorWithCalibratedRed(Ctx *ctx,knh_sfp_t *sfp)
{
	float color_red  = p_float(sfp[1]);
	float color_green = p_float(sfp[2]);
	float color_blue = p_float(sfp[3]);
	float color_alpha = p_float(sfp[4]);
	knh_Glue_t *ret =(knh_Glue_t *) new_Glue(ctx,"This",NULL,NULL);
	NSColor *color = [NSColor colorWithCalibratedRed:color_red green:color_green
		blue:color_blue alpha:color_alpha];
	ret->ptr = (void *)color;
	KNH_RETURN(ctx,sfp,ret);
}
//end NSColor


