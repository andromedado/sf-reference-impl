//
//  FDSCServiceManager.h
//  1stdibs
//
//  Created by Shad Downey on 3/22/17.
//  Copyright © 2017 1stdibs. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface FDSCServiceManager : NSObject

+ (instancetype) sharedInstance;

- (void) setup;

@end
