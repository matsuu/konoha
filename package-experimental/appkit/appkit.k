class NSAutoreleasePool;
class NSWindow;
class NSApplication;
class NSSound;
class NSView;
class NSButton extends NSView;
class NSColor;
class NSImage;
class NSBox;

NSAutoreleasePool NSAutoreleasePool.new();
void NSAutoreleasePool.drain();

NSWindow NSWindow.new();
void NSWindow.initWithContentRect(float x, float y, float w, float h);
void NSWindow.setTitle(String title);
void NSWindow.setLevel(int level);
void NSWindow.display();
void NSWindow.center();
void NSWindow.orderFrontRegardless();
void NSWindow.setBackgroundColor(NSColor color);
void NSWindow.becomeKeyWindow();
NSView NSWindow.contentView();


NSApplication NSApplication.new();
void NSApplication.run();

NSSound NSSound.new();
void NSSound.initWithContentsOfFile(String filepath);
void NSSound.play();

NSButton NSButton.new();
void NSButton.initWithFrame(float x,float y,float w, float h);


NSView NSView.new();
void NSView.initWithFrame(float x,float y,float w, float h);
void NSView.addSubview(NSButton button);
void NSView.lockFocus();

NSColor NSColor.new();
NSColor NSColor.colorWithCalibratedRed(float red,float green,float blue,float alpha);


NSImage NSImage.new();
NSImage NSImage.initByReferencingFile(String filename);

