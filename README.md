# Description

MyTarget plugin for sdkbar plugin system. It has mediation libraries for AdMob.

# Installation

`sdkbar -i https://github.com/OrangeAppsRu/sdkbar-mytarget`

# Dependencies

This plugin have no dependencies.

# Plugin JS interface

- `mytarget.init()`
- `mytarget.loadBanner(slot_id, callback_function, callback_this)`
- `mytarget.showBanner(callback_function, callback_this)`
- `mytarget.removeBanner(callback_function, callback_this)`
- `mytarget.loadFullScreen(slot_id, callback_function, callback_this)`
- `mytarget.showFullScreen(callback_function, callback_this)`
- `mytarget.setUserConsent(bool_flag)`
- `mytarget.setUserAgeRestricted(bool_flag)`
