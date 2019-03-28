//
//  MTRGMediaAdView.h
//  myTargetSDK 5.0.4
//
//  Created by Andrey Seredkin on 19.08.16.
//  Copyright © 2016 Mail.ru. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface MTRGMediaAdView : UIView

@property(nonatomic, readonly) UIImageView *imageView;
@property(nonatomic, readonly) UIImageView *playImageView;
@property(nonatomic, readonly) UIActivityIndicatorView *activityIndicatorView;

+ (instancetype)create;

@end

NS_ASSUME_NONNULL_END
