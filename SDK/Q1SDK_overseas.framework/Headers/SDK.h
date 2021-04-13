//
//  SDK.h
//  SDK
//
//  Created by luo on 2019/3/19.
//  Copyright © 2019 luo. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "ResponseModel.h"

typedef enum {
    SDK_InitFinish = 0,   //初始化完成
    SDK_LoginSuccess,     //登录成功
    SDK_LoginFail,        //登录失败
    SDK_IdAuthSuccess,    //实名认证成功
    SDK_IdAuthCancel,     //取消
    SDK_PaySuccess,       //支付成功
    SDK_PayFail,          //支付失败
    SDK_PayCancel,        //支付取消
} SDK_EventType;

typedef enum {
    region_cn     = 0,    //国内
    region_ea     = 1,    //欧美
    region_sa     = 2,    //东南亚
    region_review = 3,    //预演
    region_debug  = 4,    //debug
} SDK_Region;

typedef enum {
    en      = 0,          //英文
    zh_hans = 1,          //中文简体
    zh_hant = 2,          //中文繁体
} SDK_Language;

typedef enum {
    LoginPlatform_Guest    = 0,      //游客
    LoginPlatform_Facebook = 1,      //Facebook
    LoginPlatform_Apple    = 7,      //Apple
} SDK_LoginPlatform;

typedef enum {
    Share_success = 0,     //分享成功
    Share_Fail,            //分享失败
    Share_Cancel,          //分享取消
} SDK_ShareResult;

typedef void (^ResponseBlock)(BOOL success, ResponseModel *response);
typedef void (^shareBlock)(SDK_ShareResult result, NSString *errMsg);

@protocol SDKDelegate <NSObject>
@optional
//回调方法
- (void)sendBack:(SDK_EventType)eventType CallbackInfo:(id)info;
@end

@interface SDK : NSObject

#pragma mark - public method

+ (SDK *)Instance;

/**
 *  初始化SDK
 *
 *  @param APPID 应用Id
 *  @param APPKEY 应用钥匙
 */

- (void)SDKInit:(id<SDKDelegate>)delegate
          APPID:(NSString *)APPID
         APPKEY:(NSString *)APPKEY;

/**
 *  登录接口  包含冰川登录注册、游客登录 facebook/AppleSignin登录
 */
- (void)SDKLogin;

/**
*  切换账号
*/
- (void)SDKSwitchAccount;

/**
*  绑定第三方账号
*
*/
- (void)bindThirdAccount;

/**
 *   活动网页
 */
- (void)SDKEventWeb:(NSString *)url;

/**
 *   设置log模式
 *   @param log  YES:打开  NO:关闭
 */
- (void)SetLog:(BOOL)log;

/**
 *   设置region 设置大区中心
 *   @param region
 region_cn = 0,    //国内
 region_ea,          //欧美
 region_sa,          //东南亚
 region_review,    //预演
 region_debug,    //debug
 */
- (void)setRegion:(SDK_Region)region;

/**
 *   设置语言
 *   默认跟随系统语言
 *   @param language  en:英文  zh_hans:中文简体  zh_hant:中文繁体
 */
- (void)setLanguage:(SDK_Language)language;

/**
 *   实名认证
 * @param closable   是否可以关闭弹框按钮  YES:可关闭 NO:不可关闭
 */
- (void)SDKIdAuth:(BOOL)closable;

/**
 *   是否实名认证
 */
- (int)SDKIsIdAuth;

/**
 *  facebook分享链接
 *  @param urlString   链接字符串
 *  @param handle          分享回调
*/
- (void)FBShareWithURL:(NSString *)urlString compationhandle:(shareBlock)handle;

/**
 *  facebook分享图片
 *  注意：必须安装Facebook APP才可分享图片
 *  @param image            image对象
 *  @param handle          分享回调
*/
- (void)FBShareWithImage:(UIImage *)image compationhandle:(shareBlock)handle;

/**
 *  开启推送功能
 *  须按文档进行相关配置
 */
- (void)openPushNotification;

/**
 *  回调注册通知的deviceToken
 *  @param deviceToken
 *  appdelegate中回调的推送设备token参数
 *  application:didRegisterForRemoteNotificationsWithDeviceToken:
*/
- (void)pushNotiDeviceToken:(NSData *)deviceToken;

/**
 *  注册推送失败
 *  @param error  失败原因
 *  appdelegate中回调的推送设备token参数
 *  application:didFailToRegisterForRemoteNotificationsWithError:
*/
- (void)pushNotiRegisterFail:(NSError *)error;

#pragma mark --------------------支付---------------------

/**
 *  支付接口
 *
 *  @param productIdentifiers     内购产品ID
 *  @param serverId                           服务区ID
 *  @param userId                               用户ID：
 *  @param payNum                               购买金额
 *  @param orderItem                         订单明细: 1*100*1*大礼包*ProductId  商品ID*单价（分）*数量*商品名称，总长度限制32个字节
 *  @param orderNO                             订单号：
 *  @param orderSign                        订单签名: MD5(OrderItem + OrderNO + PayNum + UserID + buyKey)
 *  @param developerPayload        游戏透传额外参数
 */
- (void)IAP_ProductId:(NSString *)productIdentifiers
              actorId:(NSString *)actorId
             serverId:(NSString *)serverId
               userId:(NSString *)userId
               payNum:(NSString *)payNum
            orderItem:(NSString *)orderItem
              orderNO:(NSString *)orderNO
         currencyType:(NSString *)currencyType
            orderSign:(NSString *)orderSign
     developerPayload:(NSString *)developerPayload;

#pragma mark --------------------事件上报---------------------

/**
 *  开始更新
 *  @brief  游戏开始更新资源时上报
 */
- (void)trackUpdateBegin;

/**
 *  更新完成
 *  @brief  游戏更新资源完成后上报
 */
- (void)trackUpdateEnd;

/**
 *  更新失败
 *  @brief  游戏更新资源完成后上报
 *  @param  msg    非必传      错误原因，格式:msg=reason,如网络错误：msg=网络错误
 */
- (void)trackUpdateError:(NSString *)msg;

/**
 * 用户校验成功
 * @brief  在游戏校验session成功之后调用
 * @param serverId     非必传        服务器id
 * @param userId         必传            用户id
 * @param roleId         非必传        角色id
 * @param roleName    非必传        角色名
 * @param roleLevel  非必传        角色等级
 */
- (void)trackUserLogin:(NSString *)serverId
                userId:(NSString *)userId
                roleId:(NSString *)roleId
              roleName:(NSString *)roleName
             roleLevel:(NSString *)roleLevel;

/**
 * 用户校验失败
 * @brief  在游戏校验session失败时调用
 * @param serverId     非必传      服务器id
 * @param userId          必传         用户id
 * @param roleId          非必传      角色id
 * @param roleName     非必传      角色名
 * @param roleLevel   非必传      角色等级
 * @param msg                非必传      错误原因，格式:msg=reason,如网络错误：msg=网络错误
 */
- (void)trackUserLoginError:(NSString *)serverId
                     userId:(NSString *)userId
                     roleId:(NSString *)roleId
                   roleName:(NSString *)roleName
                  roleLevel:(NSString *)roleLevel
                        msg:(NSString *)msg;
/**
 * 选择服务器
 * @brief 用户登录成功，选择服务器时上报
 * @param serverId      必传        服务器id
 * @param userId          必传         用户id
 * @param roleId          非必传     角色id
 * @param roleName     非必传      角色名
 * @param roleLevel   非必传      角色等级
 */
- (void)trackSelectServer:(NSString *)serverId
                   userId:(NSString *)userId
                   roleId:(NSString *)roleId
                 roleName:(NSString *)roleName
                roleLevel:(NSString *)roleLevel;

/**
 * 创建角色
 * @brief 创建角色时上报
 * @param serverId      必传        服务器id
 * @param userId          必传         用户id
 * @param roleId          非必传     角色id
 * @param roleName     非必传      角色名
 * @param roleLevel   非必传      角色等级
 */
- (void)trackCreateRole:(NSString *)serverId
                 userId:(NSString *)userId
                 roleId:(NSString *)roleId
               roleName:(NSString *)roleName
              roleLevel:(NSString *)roleLevel;

/**
 * 角色登录
 * @brief 游戏角色登录时上报，新创建角色登录也应上报登录事件
 * @param serverId      必传        服务器id
 * @param userId          必传         用户id
 * @param roleId          必传         角色id
 * @param roleName     必传          角色名
 * @param roleLevel   必传      角色等级
 */
- (void)trackRoleLogin:(NSString *)serverId
                userId:(NSString *)userId
                roleId:(NSString *)roleId
              roleName:(NSString *)roleName
             roleLevel:(NSString *)roleLevel;

/**
 * 角色升级
 * @brief 游戏角色升级时上报
 * @param serverId      必传        服务器id
 * @param userId          必传         用户id
 * @param roleId          必传         角色id
 * @param roleName     必传         角色名
 * @param roleLevel   必传         角色等级
 */
- (void)trackLevelUp:(NSString *)serverId
              userId:(NSString *)userId
              roleId:(NSString *)roleId
            roleName:(NSString *)roleName
           roleLevel:(NSString *)roleLevel;

/**
 *  启动日志
 *  @param action    动作：updateEnd，updateError，openSDK
 *  @param msg       上报消息(根据需求定义)：ver=2018042501;update=100%
 */
- (void)SDKEventReport:(NSString *)action
                   msg:(NSString *)msg;

/**
 *  登录日志，有用户角色信息的调用是事件，如：创建角色，登录进入游戏，SDK账号验证成功
 *  @param action     事件类型
 *  @param serverId   服务器id
 *  @param actorId     角色ID
 *  @param actorName  角色名称
 *  @param actorLevel 角色等级
 *  @param user       用户名或userid(通过session从服务器取)
 *  @param msg        如：skin=red;eye=cockeye(根据需求定义)
 */
- (void)SDKEvent:(NSString *)action
        serverID:(NSString *)serverId
         actorId:(NSString *)actorId
       actorName:(NSString *)actorName
      actorLevel:(NSString *)actorLevel
            user:(NSString *)user
             msg:(NSString *)msg;

#pragma mark --------------------基础数据---------------------
- (NSString *)shortVersion;
- (NSString *)GetPID;
- (NSString *)GetUUID;
- (NSString *)GetIPAddress;
- (NSString *)GetRadid;
- (NSString *)GetRsid;

#pragma mark --------------------无UI参数---------------------
//获取userid
- (NSString *)getUserId;

//获取是否有第二次登录
- (BOOL)isSecondLogin;
//获取防沉迷标志(0未填写身份证 1已成年 2未成年)
- (int)nonKid;

//是否支持Apple登录 （iOS 13及以上）
- (BOOL)isSupportAppleSignin;

//最近登录账号平台
- (SDK_LoginPlatform)getLatestLoginPlatform;

//最近登录账号信息
- (NSDictionary *)lastLoginUser;

#pragma mark --------------------接口透传（无界面）---------------------

/**
 *   游客登录
 *   @param block  返回数据
 */
- (void)guestLogin:(ResponseBlock)block;

/**
*   自动登录  session自动刷新，返回最新session
*   @param block  返回数据
*/
- (void)getLatestSession:(ResponseBlock)block;

/**
*   使用上次登录方式登录,session刷新失败时调用
*   @param block  返回数据
*/
- (void)loginWithLatestLoginPlatform:(ResponseBlock)block;

/**
 *  facebook登录
 *  @param block  返回数据
 */
- (void)FacebookLogin:(ResponseBlock)block;

/**
 *  AppleSignin登录
 *  @param block  返回数据
 */
- (void)AppleLogin:(ResponseBlock)block;

/**
 *  切换账号前调用(清除fb账号缓存)
 */
- (void)Facebooklogout;

/**
 *  facebook绑定
 *  @param block  返回数据
 */
- (void)FacebookBind:(ResponseBlock)block;

/**
 *  Apple绑定
 *  @param block  返回数据
 */
- (void)AppleBind:(ResponseBlock)block;

/**
 *   实名认证
 *   @param realName   真实姓名
 *   @param IDNo       身份证号码
 */
- (void)realNameCerification:(NSString *)realName
                        IDNo:(NSString *)IDNo
                       block:(ResponseBlock)block;

#pragma mark - private method
- (void)SendMessage:(SDK_EventType)eventType data:(id)data;

@end
