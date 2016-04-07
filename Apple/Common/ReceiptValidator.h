//
//  ReceiptValidator.h
//  MawKit
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 19/03/16.
//
//

#import <Foundation/Foundation.h>

@interface ReceiptValidator : NSObject

+ (BOOL)receiptAtURL:(NSURL *)receiptURL
  isValidForBundleID:(NSString *)bundleID
          andVersion:(NSString *)version;

+ (BOOL)appReceiptIsValidForBundleID:(NSString *)bundleID
                          andVersion:(NSString *)version;

+ (void)validateAppReceiptForBundleID:(NSString *)bundleID
                           andVersion:(NSString *)version;

@end
