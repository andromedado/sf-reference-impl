//
//  ViewController.m
//  SFReferenceImpl
//
//  Created by Shad Downey on 3/22/17.
//  Copyright © 2017 Shad Downey. All rights reserved.
//

#import "ViewController.h"

@import ServiceCore;
@import ServiceKnowledge;

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
}

- (IBAction)buttonTap:(id)sender {
    [[SCServiceCloud sharedInstance].knowledge setInterfaceVisible:YES
                                                          animated:YES
                                                        completion:nil];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
