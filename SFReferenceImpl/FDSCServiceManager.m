//
//  FDSCServiceManager.m
//  1stdibs
//
//  Created by Shad Downey on 3/22/17.
//  Copyright © 2017 1stdibs. All rights reserved.
//

#import "FDSCServiceManager.h"

@import ServiceCore;
@import ServiceKnowledge;

@interface FDSCServiceManager () <SCServiceCloudDelegate>

@end

@implementation FDSCServiceManager

+ (instancetype) sharedInstance {
    static FDSCServiceManager *instance = nil;

    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        instance = [[FDSCServiceManager alloc] initPrivate];
    });

    return instance;
}

- (id) init {
    [NSException raise:@"Singleton Class" format:@"Use `+sharedInstance` instead of new/init"];
    return nil;
}

- (id) initPrivate {
    return [super init];
}

- (BOOL)serviceCloud:(SCServiceCloud *)serviceCloud shouldShowActionWithName:(NSString*)name
{
    return YES;
}

- (void)serviceCloud:(SCServiceCloud*)serviceCloud serviceAuthenticationFailedWithError:(NSError*)error
{
    NSLog(@"UGH OH!");
}

- (void) setup {
    // Create configuration object with init params
    SCSServiceConfiguration *config = [[SCSServiceConfiguration alloc]
                                       initWithCommunity:[NSURL URLWithString:@"https://support.1stdibs.com"]
                                       dataCategoryGroup:@"Public"
                                       rootDataCategory:@"All"];

    // Perform any additional configuration here

    // Pass configuration to shared instance
    [SCServiceCloud sharedInstance].serviceConfiguration = config;
    [SCServiceCloud sharedInstance].knowledge.enabled = YES;
    [SCServiceCloud sharedInstance].delegate = self;

    // Create appearance configuration object with some appearance changes
    SCAppearanceConfiguration *appearance = [SCAppearanceConfiguration new];

    UIFontDescriptor *descriptor = [[UIFontDescriptor alloc] initWithFontAttributes:
                                    @{
                                      UIFontDescriptorFamilyAttribute: @"FreightSansProBook-Regular"
                                      }];
    [appearance setFontDescriptor:descriptor fontFileName:@"FreigSanProBook.otf" forWeight:SCFontWeightLight];
    [appearance setFontDescriptor:descriptor fontFileName:@"FreigSanProBook.otf" forWeight:SCFontWeightRegular];

    UIFontDescriptor* boldDesc = [[UIFontDescriptor alloc] initWithFontAttributes:@{
                                                                                    UIFontDescriptorFamilyAttribute:@"BryantPro-Medium.otf"
                                                                                    }];
    [appearance setFontDescriptor:boldDesc fontFileName:@"BryantPro-Medium.otf" forWeight:SCFontWeightBold];

    // Pass appearance configuration to shared instance
    [SCServiceCloud sharedInstance].appearanceConfiguration = appearance;

    SCSKnowledgeManager *knowledgeManager = [SCSKnowledgeManager defaultManager];
    if (!knowledgeManager.hasFetchedCategories) {

        [knowledgeManager fetchAllCategoriesWithCompletionHandler:^
         (NSArray<SCSCategoryGroup *> * _Nullable categoryGroups,
          NSError * _Nullable error) {

             // TO DO: Get articles from each category using queryArticlesInCategory
             NSLog(@"Yeah ? %@", @(knowledgeManager.hasFetchedCategories));
             NSLog(@"Yeah ! %@", categoryGroups);
             NSLog(@"Nah ! %@", error);
             NSLog(@"blergh");

         }];
    }

    [[SFLogger sharedLogger] setLogLevel:SFLogLevelVerbose
                forIdentifiersWithPrefix:@"com.salesforce.ServiceSDK"];
}

@end
