#!/usr/local/bin/konoha

using appkit.*;

NSAutoreleasePool pool = new NSAutoreleasePool();

NSApplication app = new NSApplication();
NSWindow win = new NSWindow();


win.initWithContentRect(200,300,250, 100);
win.setTitle("HelloWorld");
win.setLevel(3);

NSButton hel = new NSButton();
hel.initWithFrame(85,10,80,80);
NSView v = win.contentView();
v.addSubview(hel);
NSColor color = new NSColor();
color = NSColor.colorWithCalibratedRed(0,1,0,1);
win.setBackgroundColor(color);
win.orderFrontRegardless();

win.display();
win.center();

app.run();

pool.drain();
