//
//  SCSArticleViewControllerDelegate.h
//  KnowledgeUI
//
//  Created by Michael Nachbaur on 9/19/16.
//  Copyright © 2016 Salesforce.com. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@class SCSArticleViewController, SCSArticle, SCSCategory;

/**
 Delegate protocol used to interact with article view controllers.
 */
@protocol SCSArticleViewControllerDelegate <NSObject>

@optional

/**
 Message sent to the delegate when the selected category is changed.

 @param controller  The article view controller.
 @param category The new category.
 */
- (void)articleController:(SCSArticleViewController*)controller categoryDidChange:(SCSCategory*)newCategory;

/**
 Informs the delegate when an article will be shown.
 
 This message is sent immediately upon setting a new article.

 @param controller The article view controller.
 @param article    The article to be displayed, or `nil` if no article is selected.
 */
- (void)articleController:(SCSArticleViewController*)controller willShowArticle:(nullable SCSArticle*)article;

/**
 Informs the delegate when an article has finished being shown.
 
 This is sent when the article has finished loading and is displayed on the screen.  If the view controller isn't initially presented in the view hierarchy when the article is initially set, this message may be delayed until the controller is eventually presented and the article is loaded.

 @param controller The article view controller.
 @param article    The article being shown, or `nil` if no article is selected.
 */
- (void)articleController:(SCSArticleViewController*)controller didShowArticle:(nullable SCSArticle*)article;

/**
 The target height for the given header view.

 If this method isn't implemented, the height for the article header will be determined automatically.  If a header view isn't to be used for this article, this method is never called.

 @param controller The article view controller.
 @param headerView The header view to be displayed.

 @return Positive float value for the desired target header view height.
 */
- (CGFloat)articleController:(SCSArticleViewController*)controller heightForHeaderView:(UIView*)headerView;

/**
 Header view to display above the article.
 
 If this method isn't implemented, a default header view will be used if an image is available for this article.  If you do not wish for a header to be displayed, you can return `nil` from this method to opt out of displaying a header.
 
 Auto Layout rules will be applied when adding this view to the hierarchy.

 @param controller The article view controller.
 @param article    The article being displayed.

 @return UIView instance to be used within the header, or `nil`.
 */
- (nullable UIView *)articleController:(SCSArticleViewController*)controller headerViewForArticle:(SCSArticle*)article;

@end

NS_ASSUME_NONNULL_END
