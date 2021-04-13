//
//  ViewController.m
//  SDKDemo
//
//  Created by mac on 2021/2/26.
//

#import "ViewController.h"
#import <Q1SDK_overseas/SDK.h>
#import <Q1SDK_overseas/ResponseModel.h>
#import <Q1SDK_overseas/ReportDataHelper.h>

@interface ViewController ()<SDKDelegate>

@property (weak, nonatomic) IBOutlet UILabel *account;
@property (weak, nonatomic) IBOutlet UILabel *accountType;
@property (weak, nonatomic) IBOutlet UITextView *logTextview;
@property (weak, nonatomic) IBOutlet UITextField *action;
@property (weak, nonatomic) IBOutlet UITextField *serverId;
@property (weak, nonatomic) IBOutlet UITextField *actorId;
@property (weak, nonatomic) IBOutlet UITextField *actorLevel;
@property (weak, nonatomic) IBOutlet UITextField *actorName;
@property (weak, nonatomic) IBOutlet UITextField *userId;
@property (weak, nonatomic) IBOutlet UITextField *message;
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(logTextInfo:) name:@"q1showLogInfoNoti" object:nil];
    
    [[SDK Instance] SetLog:YES];
    [[SDK Instance] setRegion:region_ea]; // 2107  904EF938-6B93-1CC8-10DD-8CA5367AB99A
    [[SDK Instance] SDKInit:self APPID:@"2118" APPKEY:@"j9a9e16f68374dddabcf345e6f1bb82a"];
}

#pragma mark - Login&Bind

- (IBAction)autoLogin:(id)sender {
    
    [[SDK Instance] getLatestSession:^(BOOL success, ResponseModel *response) {
        if (success) {
            [self showLogWithTitle:[NSString stringWithFormat:@"自动登录%@",success?@"成功":@"失败"] Msg:[NSString stringWithFormat:@"%@%@",response.info,response.responseDic]];
        } else {
            [self showLogWithTitle:@"刷新session失败" Msg:[NSString stringWithFormat:@"%@%@",response.info,response.responseDic]];
            [[SDK Instance] loginWithLatestLoginPlatform:^(BOOL success, ResponseModel *response) {
                [self showLogWithTitle:[NSString stringWithFormat:@"自动登录%@",success?@"成功":@"失败"] Msg:[NSString stringWithFormat:@"%@%@",response.info,response.responseDic]];
                [self updateAccountStatus];
                NSLog(@"登录%@ %@ %@",success?@"成功":@"失败",response.info,response.responseDic);
            }];
        }
        
    }];
    [self updateAccountStatus];
}

- (IBAction)guestLogin:(id)sender {
    [[SDK Instance] guestLogin:^(BOOL success, ResponseModel *response) {
        if (success) {
            // 登录成功
            [self showLogWithTitle:@"登陆成功" Msg:[NSString stringWithFormat:@"%@",response.responseDic]];
            [self updateAccountStatus];
        }else{
            //提示语显示：response.info
            [self showLogWithTitle:@"登陆失败" Msg:[NSString stringWithFormat:@"%@",response.info]];
        }
    }];
    
}

- (IBAction)facebookLogin:(id)sender {
    [[SDK Instance] FacebookLogin:^(BOOL success, ResponseModel *response) {
        [self showLogWithTitle:[NSString stringWithFormat:@"Facebook登录%@",success?@"成功":@"失败"] Msg:[NSString stringWithFormat:@"%@%@",response.info,response.responseDic]];
        [self updateAccountStatus];
        NSLog(@"facebook登录%@ %@ %@",success?@"成功":@"失败",response.info,response.responseDic);
    }];
    
}

- (IBAction)facebookBind:(id)sender {
    [[SDK Instance] FacebookBind:^(BOOL success, ResponseModel *response) {
        [self showLogWithTitle:[NSString stringWithFormat:@"Facebook绑定%@",success?@"成功":@"失败"] Msg:[NSString stringWithFormat:@"%@%@",response.info,response.responseDic]];
        NSLog(@"facebook绑定%@ %@ %@",success?@"成功":@"失败",response.info,response.responseDic);
    }];
}

- (IBAction)fblogout:(id)sender {
    [[SDK Instance] Facebooklogout];
}

- (IBAction)appleLogin:(id)sender {
    
    [[SDK Instance] AppleLogin:^(BOOL success, ResponseModel *response) {
        [self showLogWithTitle:[NSString stringWithFormat:@"Apple登录%@",success?@"成功":@"失败"] Msg:[NSString stringWithFormat:@"%@%@",response.info,response.responseDic]];
        [self updateAccountStatus];
        NSLog(@"Apple登录%@ %@ %@",success?@"成功":@"失败",response.info,response.responseDic);
    }];
}

- (IBAction)applebind:(id)sender {
    [[SDK Instance] AppleBind:^(BOOL success, ResponseModel *response) {
        [self showLogWithTitle:[NSString stringWithFormat:@"Apple绑定%@",success?@"成功":@"失败"] Msg:[NSString stringWithFormat:@"%@%@",response.info,response.responseDic]];
        NSLog(@"Apple绑定%@ %@ %@",success?@"成功":@"失败",response.info,response.responseDic);
    }];
}

#pragma mark - trackEvent

- (IBAction)startEvent:(id)sender {
    [[SDK Instance] SDKEventReport:self.action.text         msg:self.message.text];
}

- (IBAction)userEvent:(id)sender {
    [[SDK Instance] SDKEvent:_action.text
                    serverID:_serverId.text
                     actorId:_actorId.text
                   actorName:_actorName.text
                  actorLevel:_actorLevel.text
                        user:_userId.text
                         msg:_message.text];
}

#pragma mark - openLink

- (IBAction)openWebPage:(id)sender {
    [[SDK Instance] SDKEventWeb:@"http://www.baidu.com"];
}

#pragma mark - IAPPay

- (IBAction)clickPayAction:(UIButton *)sender {

//    [[SDK Instance] IAP_ProductId:@"q1_hero_ap5"
//                          actorId:@"3577765"
//                         serverId:@"1104"
//                           userId:@"147856239"
//                           payNum:@"4.99"
//                        orderItem:@"24534*199*1*觉醒英雄1低V本体+进阶石*q1_hero_ap20445f00000bf800055f6544f79439ab51.991860907USD123456"
//                          orderNO:@"06bb60000045000055f0fb72203ae37d"
//                     currencyType:@"USD"
//                        orderSign:@"dc8306763a735d4cc7a4e450209f18f4"];
    
//    [[SDK Instance] IAP_ProductId:@"ocean_120gems"
//                          actorId:@"943160201"
//                         serverId:@"60202"
//                           userId:@"1736028"
//                           payNum:@"0.99"
//                        orderItem:@"*99*1*60 Red Gems*ocean_120gems"
//                          orderNO:@"5778c9fa26984f9c9ee6b19f2c151d92"
//                     currencyType:@"USD"
//                        orderSign:@"da67802f38344ad0bd88cea2b4fcbc47"
//                 developerPayload:@""];
    
    [[SDK Instance] IAP_ProductId:@"ocean_120gems"
                          actorId:@"943160201"
                         serverId:@"70101"
                           userId:@"1845902"
                           payNum:@"0.99"
                        orderItem:@"*99*1*60红钻*ocean_120gems"
                          orderNO:@"b041de16e8c9403d9f8df54bd7ce3365"
                     currencyType:@"USD"
                        orderSign:@"7f3c3703db17f2bab73bff70237f603f"
                 developerPayload:@""];
}

#pragma mark - Share

- (IBAction)shareWithLink:(id)sender {
    [[SDK Instance] FBShareWithURL:@"http://www.baidu.com" compationhandle:^(SDK_ShareResult result, NSString *errMsg) {
        NSLog(@"%@",errMsg);
    }];
}

- (IBAction)shareWithImage:(id)sender {
    UIImage *image = [UIImage imageNamed:@"q1logomain"];
    
    [[SDK Instance] FBShareWithImage:image compationhandle:^(SDK_ShareResult result, NSString *errMsg) {
        NSLog(@"%@",errMsg);
    }];
}

#pragma mark - SDKDelegate

-(void)sendBack:(SDK_EventType)eventType CallbackInfo:(id)info {
    if (eventType == SDK_InitFinish) {
        [self showLogWithTitle:@"提示" Msg:@"SDK初始化成功！"];
    } else if (eventType == SDK_LoginSuccess) {
//        [self updateAccountStatus];
        NSString* s = [[NSString alloc] initWithFormat:@"%@|%@",[info objectForKey:@"session"],[info objectForKey:@"userid"]];
        //NSLog(@"%@",[NSString stringWithFormat:@"%@",[[info GetData] GetSession]]);
//        UnitySendMessage("PluginPlatform", "SDKLoginCallback",[s UTF8String]);
    } else if (eventType == SDK_LoginFail) {
        
    } else if (eventType == SDK_IdAuthSuccess) {
//        UnitySendMessage("PluginPlatform", "IdAuthCallback","1");
    } else if (eventType == SDK_IdAuthCancel) {
//        UnitySendMessage("PluginPlatform", "IdAuthCallback","0");
    } else if (eventType == SDK_PaySuccess) {
        
    } else if (eventType == SDK_PayFail) {
        [self showLogWithTitle:@"提示" Msg:[NSString stringWithFormat:@"%@",info]];
    } else if (eventType == SDK_PayCancel) {
        [self showLogWithTitle:@"提示" Msg:[NSString stringWithFormat:@"%@",info]];
    }
    NSLog(@"收到了回调 ：%@",info);
}

#pragma mark - log

- (void)logTextInfo:(NSNotification *)noti {
    NSDictionary *dic = noti.userInfo;
    [self addPrintWithMessage:[dic objectForKey:@"log"]];
}

- (void)addPrintWithMessage:(NSString *)msg {
    dispatch_async(dispatch_get_main_queue(), ^{
        @synchronized (self) {
            if (self.logTextview.text.length) {
                self.logTextview.text = [NSString stringWithFormat:@"%@\n%@", self.logTextview.text, msg];
            } else {
                self.logTextview.text = msg;
            }
            [self.logTextview scrollRangeToVisible:NSMakeRange(MAX((self.logTextview.text.length - 1), 0), self.logTextview.text.length ? 1 : 0)];
        }
    });
}


-(void)showLogWithTitle:(NSString *)title Msg:(NSString *)msg {
//    self.logTextview.text = [NSString stringWithFormat:@"%@ \n %@",title,msg];
    NSLog(@"%@%@",title,msg);
}

-(void)updateAccountStatus {
    
    NSDictionary *resDic = [[SDK Instance] lastLoginUser];
    
//    self.account.text = [[resDic objectForKey:@"userid"] stringValue];
    
    self.account.text = [[SDK Instance] getUserId];
    NSInteger logintype = [[resDic objectForKey:@"userType"] integerValue];
    
    NSString *loginTypeStr = @"未知";
    switch (logintype) {
        case 0:
            loginTypeStr = @"Guest";
            break;
            
        case 1:
            loginTypeStr = @"Facebook";
            break;
        
        case 7:
            loginTypeStr = @"Apple";
            break;
            
        default:
            break;
    }
    
    self.accountType.text = loginTypeStr;
}

- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    [self.view endEditing:YES];
}

@end
