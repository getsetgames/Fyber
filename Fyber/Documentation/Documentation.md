<h1>Fyber Integration Guide</h1>

<h2>Prerequisites</h2>
For Android, Fyber requires a minimum version of 4.0.3. This version is newer than what the other SDKBOX plugins require.
Certain SDKBOX plugins do not work together. If you use Fyber, then you cannot also use the SOOMLA GROW services, in the same project.
Integration


<h2>Important Notice</h2>
If you upgraded to Xcode7 you need to perform the following steps to your project for plugin to function correctly.

<h3>Disable App Transport Security</h3>

Adding the following entry to the info.plist file:

<key>NSAppTransportSecurity</key>
<dict>
    <key>NSAllowsArbitraryLoads</key>
    <true/>
</dict>
It should look something like this:



<h3>Disable Bitcode support</h3>

You have to turn off Bitcode support. If you don't cocos2d-x will fail to build.

Set your game requires full screen

If your game doesn't support all screen orientations you will need to check Requires full screen in Xcode. If you do not, your app will fail Apple's submission process.

Whitelist canOpenURL function

This depends on what plugins are in your project. You may need to add the required entry to the info.plist, under LSApplicationQueriesSchemes.


<h2>Extra Steps</h2>


The following step assuming you already registered as a Fyber Developer And created a new APP on Fyber

Setup iOS
Configure your APP following iOS Quick Start Guide
Setup Android
Make sure java -version >= 1.7
Configure your APP on Fyber follow Android Quick Start Guide
Setup Mediation
If you want to setup fyber to use certain mediation network, please follow fyber's official integration guide

iOS Supported networks
Android Supported networks
JSON Configuration
SDKBOX Installer will automatically create a sample configuration sdkbox_config.json for you

Here is an example of the Fyber configuration you can enable/disable debug mode for Fyber here

"Fyber":
{
    "debug":true,
    "appid":"12345",
    "token":"34a9643edf4d3052d2bc1928b2e34d00"
}


<h2>Usage</h2>
Initialize Fyber
Initialize the plugin where appropriate in your code. We recommend to do this in the

<h2>Using Fyber</h2>

<h3>Offer Wall</h3>

Displaying the Offer Wall with default placementId

sdkbox::PluginFyber::showOfferWall();
Displaying the Offer Wall with custom placementId

sdkbox::PluginFyber::showOfferWall("coins");

<h3>Rewarded Video</h3>

iOS configure follow rewarded-video-iOS
Android configure follow rewarded-video-android
Queries the server for BrandEngage offers availability with default placementId:

sdkbox::PluginFyber::requestOffers();
Queries the server for BrandEngage offers availability with custom placementId:

sdkbox::PluginFyber::requestOffers("coins");
Display an available rewarded video, call requestOffers() first and then showOffers(). Developer can requestOffers() anytime, then showOffers() without any delay:

sdkbox::PluginFyber::requestOffers();
sdkbox::PluginFyber::showOffers();

<h3>Interstitials</h3>

Check if interstitial ads are available:

sdkbox::PluginFyber::requestInterstitial();
Shows an interstitial ad. Call requestInterstitial first:

sdkbox::PluginFyber::showInterstitial();
Fetches the amount of a given currency earned since the last time this method was invoked for the current user ID / app ID combination:

sdkbox::PluginFyber::requestDeltaOfCoins();
or:

sdkbox::PluginFyber::requestDeltaOfCoins("currencyId")
Fyber events
This allows you to catch Fyber events so that you can perform operations after Fyber events have occurred.

Allow your class to extend sdkbox::FyberListener and override the functions listed:

```
#include "PluginFyber/PluginFyber.h"
class MyClass : public sdkbox::FyberListener
{
private:
    void onVirtualCurrencyConnectorFailed(int error,
                                                  const std::string& errorCode,
                                                  const std::string& errorMsg);
    void onVirtualCurrencyConnectorSuccess(double deltaOfCoins,
                                                   const std::string& currencyId,
                                                   const std::string& currencyName,
                                                   const std::string& transactionId);
    void onCanShowInterstitial(bool canShowInterstitial);
    void onInterstitialDidShow();
    void onInterstitialDismiss(const std::string& reason);
    void onInterstitialFailed();
    void onBrandEngageClientReceiveOffers(bool areOffersAvailable);
    void onBrandEngageClientChangeStatus(int status, const std::string& msg);
    void onOfferWallFinish(int status);
};
```

Create a listener that handles callbacks:
```
sdkbox::PluginFyber::setListener(this);
```

<h2>API Reference</h2>

<h3>Methods</h3>
```
static void init ( const std::string & userID = "" ) ;
initialize the fyber plugin.
static void setListener ( FyberListener * listener ) ;
Set listener to listen for fyber events
static FyberListener * getListener ( ) ;
Get the listener
static void removeListener ( ) ;
Remove the listener, and can't listen to events anymore.
static void showOfferWall ( const std::string & placementId = "" ) ;
Presents the Fyber Mobile OfferWall as a child view controller of your own view controller.
static void requestOffers ( const std::string & placementId = "" ) ;
Request the server for rewarded video availability.
static void showOffers ( const std::string & placementId = "" ) ;
Show an available rewarded video.
static void requestInterstitial ( ) ;
Check if interstitial ads are available
static void showInterstitial ( ) ;
Shows an interstitial ad. Check first that one is ready to be shown with requestInterstitial.
static void requestDeltaOfCoins ( const std::string & currencyId = "" ) ;
Fetches the amount of a given currency earned since the last time this method was invoked for the current user ID / app ID combination.
static void setAge ( int age ) ;
Sets the user's age
// "2000-02-03"
static void setBirthdate ( const std::string & data ) ;
Sets the user's date of birth, format (yyyy-MM-dd)
// sdkbox::FYB_UserGenderUndefined
// sdkbox::FYB_UserGenderMale
// sdkbox::FYB_UserGenderFemale
// sdkbox::FYB_UserGenderOther
static void setGender ( int gender ) ;
Sets the user's gender
// sdkbox::FYB_UserSexualOrientationUndefined
// sdkbox::FYB_UserSexualOrientationStraight
// sdkbox::FYB_UserSexualOrientationBisexual
// sdkbox::FYB_UserSexualOrientationGay
// sdkbox::FYB_UserSexualOrientationUnknown
static void setSexualOrientation ( int sexualOrientation ) ;
Sets the user's sexual orientation
// sdkbox::FYB_UserEthnicityUndefined
// sdkbox::FYB_UserEthnicityAsian
// sdkbox::FYB_UserEthnicityBlack
// sdkbox::FYB_UserEthnicityHispanic
// sdkbox::FYB_UserEthnicityIndian
// sdkbox::FYB_UserEthnicityMiddleEastern
// sdkbox::FYB_UserEthnicityNativeAmerican
// sdkbox::FYB_UserEthnicityPacificIslander
// sdkbox::FYB_UserEthnicityWhite
// sdkbox::FYB_UserEthnicityOther
static void setEthnicity ( int ethnicity ) ;
Sets the user's ethnicity
static void setLocation ( double latitude , double longitude ) ;
Set the user's location
static void cleanLocation ( ) ;
Clean the user's location
// sdkbox::FYB_UserMaritalStatusUndefined
// sdkbox::FYB_UserMartialStatusSingle
// sdkbox::FYB_UserMartialStatusRelationship
// sdkbox::FYB_UserMartialStatusMarried
// sdkbox::FYB_UserMartialStatusDivorced
// sdkbox::FYB_UserMartialStatusEngaged
static void setMaritalStatus ( int status ) ;
Sets the user's marital status
static void setNumberOfChildren ( int numberOfChildren ) ;
Sets the user's number of children
static void setAnnualHouseholdIncome ( int income ) ;
Sets the user's annual household income
// sdkbox::FYB_UserEducationUndefined
// sdkbox::FYB_UserEducationOther
// sdkbox::FYB_UserEducationNone
// sdkbox::FYB_UserEducationHighSchool
// sdkbox::FYB_UserEducationInCollege
// sdkbox::FYB_UserEducationSomeCollege
// sdkbox::FYB_UserEducationAssociates
// sdkbox::FYB_UserEducationBachelors
// sdkbox::FYB_UserEducationMasters
// sdkbox::FYB_UserEducationDoctorate
static void setEducation ( int education ) ;
Sets the user's educational background
static void setZipcode ( const std::string & zipcode ) ;
Sets the user's zipcode
static void setInterests ( const std::vector <std::string> & interests ) ;
Set the user's list of interests
static void setIap ( bool flag ) ;
Sets if in-app purchases are enabled.
static void setIapAmount ( float amount ) ;
Sets the amount that the user has already spent on in-app purchases
static void setNumberOfSessions ( int numberOfSessions ) ;
Sets the number of sessions
static void setPsTime ( double timestamp ) ;
Sets the time spent on the current session
static void setLastSession ( double session ) ;
Sets the duration of the last session
// sdkbox::FYB_UserConnectionTypeUndefined
// sdkbox::FYB_UserConnectionTypeWiFi
// sdkbox::FYB_UserConnectionType3G
// sdkbox::FYB_UserConnectionTypeLTE
// sdkbox::FYB_UserConnectionTypeEdge
static void setConnectionType ( int connectionType ) ;
Sets the connection type used by the user
// predefine values
// sdkbox::FYB_UserDeviceUndefined
// sdkbox::FYB_UserDeviceIPhone
// sdkbox::FYB_UserDeviceIPad
// sdkbox::FYB_UserDeviceIPod
// sdkbox::FYB_UserDeviceAndroid
static void setDevice ( const std::string & device ) ;
Sets the device used by the user
static void setVersion ( const std::string & version ) ;
Sets the app version
static void cleanCustomParameters ( ) ;
Clean custom parameters, iOS only
static void addCustomParameters ( const std::string & key ,
                                  const std::string & value ) ;
Sets custom parameters to be sent along with the standard parameters
```

<h3>Listeners</h3>
```
void onVirtualCurrencyConnectorFailed ( int error ,
                                        const std::string & errorCode ,
                                        const std::string & errorMsg );
void onVirtualCurrencyConnectorSuccess ( double deltaOfCoins ,
                                         const std::string & currencyId ,
                                         const std::string & currencyName ,
                                         const std::string & transactionId );
void onCanShowInterstitial ( bool canShowInterstitial );
void onInterstitialDidShow ( );
void onInterstitialDismiss ( const std::string & reason );
void onInterstitialFailed ( );
void onBrandEngageClientReceiveOffers ( bool areOffersAvailable );
void onBrandEngageClientChangeStatus ( int status , const std::string & msg );
void onOfferWallFinish ( int status );
```

<h2>Manual Integration</h2>

If the SDKBOX Installer fails to complete successfully, it is possible to integrate SDKBOX manually. If the installer complete successfully, please do not complete anymore of this document. It is not necessary.

These steps are listed last in this document on purpose as they are seldom needed. If you find yourself using these steps, please, after completing, double back and re-read the steps above for other integration items.

Manual Integration For iOS
Drag and drop the following frameworks from the plugins/ios folder of theFyber bundle into your Xcode project, check Copy items if needed when adding frameworks:

sdkbox.framework

PluginFyber.framework
The above frameworks depend upon a large number of other frameworks. You also need to add the following system frameworks, if you don't already have them:

```
AdSupport.framework

CoreGraphics.framework

CoreLocation.framework

CoreTelephony.framework

MediaPlayer.framework

QuartzCore.framework

StoreKit.framework

SystemConfiguration.framework

Security.framework

CFNetwork.framework

GameController.framework
```

Add separate linker flags to: Target -> Build Settings -> Linking -> Other Linker Flags:

```
-ObjC
```

Manual Integration For Android
SDKBOX supports three different kinds of Android projects command-line, eclipse and Android Studio.

proj.android will be used as our <project_root> for command-line and eclipse project
proj.android-studio will be used as our <project_root> for Android Studio project.
Copy Files
Copy the following jar files from plugin/android/libs folder of this bundle into your project’s /libs folder.

```
PluginFyber.jar

sdkbox.jar
```

If you're using cocos2d-x from source copy the jar files to:

Android command-line: cocos2d/cocos/platform/android/java/libs

Android Studio: cocos2d/cocos/platform/android/libcocos2dx/libs

If you're using cocos2d-js or lua copy the jar files to:

Android command-line: frameworks/cocos2d-x/cocos/platform/android/java/libs

Android Studio: frameworks/cocos2d-x/cocos/platform/android/libcocos2dx/libs

If you're using prebuilt cocos2d-x copy the jar files to:

Android command-line: <project_root>/libs

Copy jni libs

Copy and overwrite all the folders from plugin/android/jni to your <project_root>/jni/ directory.

Note: sdkbox link with gnustl by default, if your project link with c++static please replace the files in <project_root>/jni/<plugin_name>/libs with files in <project_root>/jni/<plugin_name>/libs_c++_static folder
Copy the fyber_lib directories from plugin/android/libs to your <project_root>/libs/ directory.

Edit AndroidManifest.xml
Include the following permissions above the application tag:

```
<uses-permission android:name="android.permission.INTERNET" />
<uses-permission android:name="android.permission.READ_PHONE_STATE" />
<uses-permission android:name="android.permission.ACCESS_NETWORK_STATE" />
<uses-permission android:name="android.permission.ACCESS_WIFI_STATE" />
There are also a few necessary meta-data tags that also need to be added:

<activity
    android:name="com.fyber.ads.ofw.OfferWallActivity"
    android:configChanges="screenSize|orientation" />
<activity
    android:name="com.fyber.ads.videos.RewardedVideoActivity"
    android:configChanges="screenSize|orientation"
    android:hardwareAccelerated="true"
  android:theme="@android:style/Theme.Translucent" />
<activity
    android:name="com.fyber.ads.interstitials.InterstitialActivity"
    android:configChanges="screenSize|orientation"
    android:theme="@android:style/Theme.Translucent" />
<activity
    android:configChanges="screenSize|orientation"
    android:name="com.fyber.cache.CacheVideoDownloadService"
    android:hardwareAccelerated="true"/>
<service android:name="com.fyber.cache.CacheVideoDownloadService" android:exported="false" />
```

Edit Android.mk
Edit <project_root>/jni/Android.mk to:

Add additional requirements to LOCAL_WHOLE_STATIC_LIBRARIES:

```
LOCAL_WHOLE_STATIC_LIBRARIES += PluginFyber
LOCAL_WHOLE_STATIC_LIBRARIES += sdkbox
```

Add a call to:

```
$(call import-add-path,$(LOCAL_PATH))
```

before any import-module statements.

Add additional import-module statements at the end:

```
$(call import-module, ./sdkbox)
$(call import-module, ./pluginfyber)
```

This means that your ordering should look similar to this:

```
$(call import-add-path,$(LOCAL_PATH))
$(call import-module, ./sdkbox)
$(call import-module, ./pluginfyber)
```

Note: It is important to make sure these statements are above the existing $(call import-module,./prebuilt-mk) statement, if you are using the pre-built libraries.

Modify Application.mk (Cocos2d-x v3.0 to v3.2 only)
Edit <project_root>/jni/Application.mk to make sure APP_STL is defined correctly. If Application.mk contains APP_STL := c++_static, it should be changed to:

```
APP_STL := gnustl_static
Add APP_PATFORM version requirements:

APP_PLATFORM := android-14
```

Modify Cocos2dxActivity.java
If you're using cocos2d-x from source, assuming you are in the proj.android directory, Cocos2dxActivity.java is located:

../../cocos2d-x/cocos/platform/android/java/src/org/cocos2dx/ lib/Cocos2dxActivity.java

If you're using the prebuilt cocos2d-x libraries assuming you are in the proj.android directory, Cocos2dxActivity.java is located:

./src/org/cocos2dx/lib/Cocos2dxActivity.java

Note: When using Cocos2d-x from source, different versions have Cocos2dxActivity.java in a different location. One way to find the location is to look in proj.android/project.properties. Example: android.library.reference.1=../../cocos2d-x/cocos/platform/android/java

In this case, Cocos2dxActivity.java should be located at:

../../cocos2d-x/cocos/platform/android/java/src/org/cocos2dx/lib/Cocos2dxActivity.java
Modify Cocos2dxActivity.java to add the following imports:

```
import android.content.Intent;
import com.sdkbox.plugin.SDKBox;
```
Second, modify Cocos2dxActivity.java to edit the onCreate(final Bundle savedInstanceState) function to add a call to SDKBox.init(this);. The placement of this call is important. It must be done after the call to onLoadNativeLibraries();. Example:

```
onLoadNativeLibraries();
SDKBox.init(this);
```
Last, we need to insert the proper overrides code. There are a few rules here.

If the method listed has not been defined, add it.

If the method listed has been defined, add the calls to SDKBox in the same existing function.

```
    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
          if(!SDKBox.onActivityResult(requestCode, resultCode, data)) {
            super.onActivityResult(requestCode, resultCode, data);
          }
    }
    @Override
    protected void onStart() {
          super.onStart();
          SDKBox.onStart();
    }
    @Override
    protected void onStop() {
          super.onStop();
          SDKBox.onStop();
    }
    @Override
    protected void onResume() {
          super.onResume();
          SDKBox.onResume();
    }
    @Override
    protected void onPause() {
          super.onPause();
          SDKBox.onPause();
    }
    @Override
    public void onBackPressed() {
          if(!SDKBox.onBackPressed()) {
            super.onBackPressed();
          }
    }
```

</h2>Proguard (optional)</h2>

Edit project.properties to specify a Proguard configuration file. Example:
proguard.config=${sdk.dir}/tools/proguard/proguard-android.txt:proguard-project.txt
Edit the file you specified to include the following:

```
# Fyber

-keep class com.fyber.** { *; }
-dontwarn com.fyber.**
-keep class com.sponsorpay.mediation.** { *;}
-keepattributes JavascriptInterface
-keep class com.sponsorpay.publisher.mbe.mediation.SPBrandEngageMediationJSInterface {
    void setValue(java.lang.String);
}
-keep class android.webkit.JavascriptInterface


# cocos2d-x
-keep public class org.cocos2dx.** { *; }
-dontwarn org.cocos2dx.**
-keep public class com.chukong.** { *; }
-dontwarn com.chukong.**

# google play service
-keep class com.google.android.gms.** { *; }
-dontwarn com.google.android.gms.**

-keep class * extends java.util.ListResourceBundle {
    protected Object[][] getContents();
}

-keep public class com.google.android.gms.common.internal.safeparcel.SafeParcelable {
    public static final *** NULL;
}

-keepnames @com.google.android.gms.common.annotation.KeepName class *
-keepclassmembernames class * {
    @com.google.android.gms.common.annotation.KeepName *;
}

-keepnames class * implements android.os.Parcelable {
    public static final ** CREATOR;
}

#sdkbox
-keep class com.sdkbox.** { *; }
-dontwarn com.sdkbox.**
```

Note: Proguard only works with Release builds (i.e cocos run -m release) debug builds do not invoke Proguard rules.

