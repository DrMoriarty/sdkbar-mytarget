package org.cocos2dx.javascript;

import android.content.Context;
import android.util.Log;
import android.app.Activity;
import android.widget.FrameLayout;
import android.view.ViewGroup;

import org.json.JSONException;
import org.json.JSONArray;
import org.json.JSONObject;

import com.my.target.ads.MyTargetView;
import com.my.target.ads.InterstitialAd;
import com.my.target.common.MyTargetPrivacy;
import org.cocos2dx.lib.Cocos2dxHelper;

public class MyTargetPlugin {
    private static final String TAG = "MyTarget";
    private static FrameLayout layout = null;
    private static MyTargetView bannerView = null;
    private static InterstitialAd fullscreenAd = null;
    public static Activity appActivity;
    private static boolean inited = false;
    private static boolean completed = false;

    static private void callCallbackResult(final int callbackId, final String error, final String result) {
        appActivity.runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    callbackResult(callbackId, error, result);
                }
            });
    }

    public static native void callbackResult(int callbackId, String err, String result);

    public static boolean init() {
        if(!inited) {
            appActivity = Cocos2dxHelper.getActivity();
            Log.i(TAG, "MyTarget initialize");
            layout = (FrameLayout)appActivity.getWindow().getDecorView().getRootView();
            /*
              if(layout instanceof AbsoluteLayout) Log.i(TAG, "AbsoluteLayout!!!");
              if(layout instanceof DrawerLayout) Log.i(TAG, "DrawerLayout!!!");
              if(layout instanceof FrameLayout) Log.i(TAG, "FrameLayout!!!");
              if(layout instanceof GridLayout) Log.i(TAG, "GridLayout!!!");
              if(layout instanceof LinearLayout) Log.i(TAG, "LinearLayout!!!");
              if(layout instanceof RelativeLayout) Log.i(TAG, "RelativeLayout!!!");
              if(layout instanceof SlidingPaneLayout) Log.i(TAG, "SlidingPaneLayout!!!");
            */
            Log.i(TAG, "Find root object with type "+layout.getClass().toString());
            inited = true;
            return true;
        }
        return false;
    }

    /*
    @Override
    public void onPause(boolean multitasking) {
        Log.i(TAG, "Paused");
        if(bannerView != null) bannerView.pause();
    }

    @Override
    public void onResume(boolean multitasking) {
        Log.i(TAG, "Resume");
        if(bannerView != null) bannerView.resume();
    }

    @Override
    public void onDestroy() {
        Log.i(TAG, "Destroy");
        if(bannerView != null) {
            bannerView.destroy();
            bannerView = null;
        }
    }
    */

    public static boolean loadBanner(final int slot, final int callbackId) {
        if(bannerView != null) {
            Log.e(TAG, "Banner view already created");
            callCallbackResult(callbackId, "Banner view already created", null);
            return false;
        }
        appActivity.runOnUiThread(new Runnable() {
                public void run() {
                    bannerView = new MyTargetView(appActivity);
                    bannerView.init(slot);

                    // Устанавливаем слушатель событий
                    bannerView.setListener(new MyTargetView.MyTargetViewListener() {
                            @Override
                            public void onLoad(MyTargetView myTargetView) {
                                // Данные успешно загружены, запускаем показ объявлений
                                Log.i(TAG, "Banner has been loaded");
                                callCallbackResult(callbackId, null, "Banner loaded");
                            }

                            @Override
                            public void onNoAd(String reason, MyTargetView myTargetView) {
                                Log.e(TAG, "No ads for banner");
                                callCallbackResult(callbackId, "No ads for banner "+slot, null);
                            }

                            @Override
                            public void onClick(MyTargetView myTargetView) {
                                Log.i(TAG, "Banner clicked");
                            }
                        });

                    // Запускаем загрузку данных
                    bannerView.load();
                }
            });
        return true;
    }

    public static boolean showBanner(final int callbackId) {
        if(bannerView == null) {
            Log.e(TAG, "Have no banner to show");
            callCallbackResult(callbackId, "You should load banner before call showBanner", null);
            return false;
        } 
        // Устанавливаем слушатель событий
        bannerView.setListener(new MyTargetView.MyTargetViewListener() {
                @Override
                public void onLoad(MyTargetView myTargetView) {
                    Log.e(TAG, "Banner has been loaded twice");
                }
                @Override
                public void onNoAd(String reason, MyTargetView myTargetView) {
                    Log.e(TAG, "No ads for loaded banner!");
                    callCallbackResult(callbackId, "No ads for loaded banner ", null);
                }
                @Override
                public void onClick(MyTargetView myTargetView) {
                    Log.i(TAG, "Banner clicked");
                    callCallbackResult(callbackId, null, "Banner clicked");
                }
            });
        // Добавляем экземпляр в лэйаут главной активности
        final FrameLayout.LayoutParams adViewLayoutParams = new FrameLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT, 0x50);
        layout.post(new Runnable() {
                public void run() {
                    Log.i(TAG, "Show new banner");
                    layout.addView(bannerView, adViewLayoutParams);
                }
            });
        return true;
    }

    public static boolean removeBanner(final int callbackId) {
        if(bannerView != null) {
            appActivity.runOnUiThread(new Runnable() {
                    public void run() {
                        layout.removeView(bannerView);
                        bannerView.destroy();
                        bannerView = null;
                        callCallbackResult(callbackId, null, "success");
                    }
                });
            return true;
        } else {
            callCallbackResult(callbackId, "No banner view", null);
            return false;
        }
    }

    public static boolean loadFullScreen(final int slot, final int callbackId) {
        appActivity.runOnUiThread(new Runnable() {
                public void run() {
                    fullscreenAd = new InterstitialAd(slot, appActivity);
                    fullscreenAd.setListener(new InterstitialAd.InterstitialAdListener() {
                            @Override
                            public void onLoad(InterstitialAd ad) {
                                Log.i(TAG, "Fullscreen ad was loaded. Slot "+slot);
                                callCallbackResult(callbackId, null, "Fullscreen loaded");
                            }

                            @Override
                            public void onNoAd(String reason, InterstitialAd ad) {
                                Log.e(TAG, "No available fullscreen ad for slot "+slot);
                                callCallbackResult(callbackId, "No ads for slot "+slot, null);
                            }

                            @Override
                            public void onClick(InterstitialAd ad) {
                                Log.i(TAG, "Click on fullscreen ad. Slot "+slot);
                            }

                            @Override
                            public void onDisplay(InterstitialAd ad) {
                                Log.i(TAG, "Display fullscreen ad. Slot "+slot);
                            }

                            @Override
                            public void onDismiss(InterstitialAd ad) {
                                Log.i(TAG, "Fullscreen ad dismiss. Slot "+slot);
                            }

                            @Override
                            public void onVideoCompleted(InterstitialAd ad) {
                                Log.i(TAG, "Fullscreen video completed. Slot "+slot);
                            }
                        });

                    // Запускаем загрузку данных
                    fullscreenAd.load();
                }
            });
        return true;
    }

    public static boolean showFullScreen(final int callbackId) {
        if(fullscreenAd == null) {
            Log.e(TAG, "Have no fullscreenAd to show");
            callCallbackResult(callbackId, "You should call loadFullScreen before showFullScreen", null);
            return false;
        }
        completed = false;
        fullscreenAd.setListener(new InterstitialAd.InterstitialAdListener() {
            @Override
            public void onLoad(InterstitialAd ad) {
                Log.e(TAG, "Fullscreen ad was loaded twice.");
            }

            @Override
            public void onNoAd(String reason, InterstitialAd ad) {
                Log.e(TAG, "No available ad for loaded fullscreen Ad");
                callCallbackResult(callbackId, "No ads for loaded fullscreen Ad ", null);
            }

            @Override
            public void onClick(InterstitialAd ad) {
                Log.i(TAG, "Click on fullscreen ad");
            }

            @Override
            public void onDisplay(InterstitialAd ad) {
                Log.i(TAG, "Display fullscreen ad");
            }

            @Override
            public void onDismiss(InterstitialAd ad) {
                Log.i(TAG, "Fullscreen ad dismiss");
                if (completed) {
                    callCallbackResult(callbackId, null, "Fullscreen ad completed");
                } else {
                    callCallbackResult(callbackId, "Fullscreen ad closed", null);
                }
            }

            @Override
            public void onVideoCompleted(InterstitialAd ad) {
                completed = true;
                Log.i(TAG, "Fullscreen video completed");
            }
        });
        fullscreenAd.show();
        return true;
    }

    public static boolean setUserConsent(boolean consent) {
        MyTargetPrivacy.setUserConsent(consent);
        return true;
    }

    public static boolean setUserAgeRestricted(boolean restricted) {
        MyTargetPrivacy.setUserAgeRestricted(restricted);
        return true;
    }
};
