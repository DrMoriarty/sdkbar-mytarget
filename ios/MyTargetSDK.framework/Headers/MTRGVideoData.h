//
//  myTargetSDK 5.0.4
//
// Created by Timur on 2/9/18.
// Copyright (c) 2018 Mail.Ru Group. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MTRGMediaData.h"

NS_ASSUME_NONNULL_BEGIN

@interface MTRGVideoData : MTRGMediaData

@property(nonatomic, readonly, copy, nullable) NSString *path;
@property(nonatomic, readonly) BOOL isCacheable;

+ (nullable MTRGVideoData *)chooseBestFromArray:(NSArray<MTRGVideoData *> *)videoDatas videoQuality:(NSUInteger)videoQuality;

+ (instancetype)videoDataWithUrl:(NSString *)url size:(CGSize)size;

@end

NS_ASSUME_NONNULL_END
