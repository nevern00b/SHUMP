//
//  ViewController.mm
//  SHMUP
//
//  Created by Philadelphia Game Lab on 4/28/14.
//  Copyright (c) 2014 Philadelphia Game Lab. All rights reserved.
//

#import "ViewController.h"
#import "Globals.h"
#include "Utils.h"
#include "UIManager.h"

@interface ViewController () {
    
}
@property (strong, nonatomic) EAGLContext *context;

- (void)setupGL;
- (void)tearDownGL;

@end

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    [self.view addGestureRecognizer:[[UIPanGestureRecognizer alloc] initWithTarget:self action:@selector(handlePan:)]];
    
    self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES3];
    
    if (!self.context) {
        NSLog(@"Failed to create ES context");
    }
    
    GLKView *view = (GLKView *)self.view;
    view.context = self.context;
    view.drawableDepthFormat = GLKViewDrawableDepthFormat24;
    view.drawableColorFormat = GLKViewDrawableColorFormatRGBA8888;
    view.drawableStencilFormat = GLKViewDrawableStencilFormatNone;
    [((GLKView*)self.view)bindDrawable];
    
    [self setupGL];
}

- (void)dealloc
{
    [self tearDownGL];
    
    if ([EAGLContext currentContext] == self.context) {
        [EAGLContext setCurrentContext:nil];
    }
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];

    if ([self isViewLoaded] && ([[self view] window] == nil)) {
        self.view = nil;
        
        [self tearDownGL];
        
        if ([EAGLContext currentContext] == self.context) {
            [EAGLContext setCurrentContext:nil];
        }
        self.context = nil;
    }

    // Dispose of any resources that can be recreated.
}

- (void)setupGL
{
    [EAGLContext setCurrentContext:self.context];
    
    NSString* directory = [[NSBundle mainBundle] resourcePath];
    const char* cpath = [directory fileSystemRepresentation];
    std::string dir = std::string(cpath) + "/";
    Utils::setDirectory(dir);
    
    float time = CACurrentMediaTime();
    uint width = self.view.bounds.size.height*2;
    uint height = self.view.bounds.size.width*2;
    Globals::init(time, width, height);
}

- (void)tearDownGL
{
    //Globals::destroy();
}

#pragma mark - GLKView and GLKViewController delegate methods

- (void)update
{
    float time = CACurrentMediaTime();
    Globals::update(time);
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    Globals::render();
}

- (void)handlePan:(UIPanGestureRecognizer *)gesture
{
    CGPoint translate = [gesture locationInView:gesture.view];
    if([gesture state] == UIGestureRecognizerStateBegan)
    {
        Globals::m_uiManager->mousePressEvent();
    }
    
    Globals::m_uiManager->mouseDownEvent();
    Globals::m_uiManager->mouseMoveEvent(translate.x*2, translate.y*2);
}

@end
