window.__require = function c(e, t, s) {
function n(i, o) {
if (!t[i]) {
if (!e[i]) {
var r = i.split("/");
r = r[r.length - 1];
if (!e[r]) {
var l = "function" == typeof __require && __require;
if (!o && l) return l(r, !0);
if (a) return a(r, !0);
throw new Error("Cannot find module '" + i + "'");
}
i = r;
}
var u = t[i] = {
exports: {}
};
e[i][0].call(u.exports, function(c) {
return n(e[i][1][c] || c);
}, u, u.exports, c, e, t, s);
}
return t[i].exports;
}
for (var a = "function" == typeof __require && __require, i = 0; i < s.length; i++) n(s[i]);
return n;
}({
main: [ function(c, e) {
"use strict";
cc._RF.push(e, "e22a5UlHvdKqbt30vd8GrHn", "main");
var t = c("mostar_fmod");
cc.Class({
extends: cc.Component,
properties: {},
start: function() {
this.paused = !1;
t.load();
},
playZhucheng: function() {
t.playMusic(t.zhucheng);
},
pauseZhucheng: function() {
t.pauseMusic(t.zhucheng);
},
resumeZhucheng: function() {
t.resumeMusic(t.zhucheng);
},
stopZhucheng: function() {
t.stopMusic(t.zhucheng);
},
playSenlin: function() {
t.playMusic(t.senlin);
},
pauseSenlin: function() {
t.pauseMusic(t.senlin);
},
resumeSenlin: function() {
t.resumeMusic(t.senlin);
},
stopSenlin: function() {
t.stopMusic(t.senlin);
},
playeffect: function() {
t.playEffect(t.bianda);
}
});
cc._RF.pop();
}, {
mostar_fmod: "mostar_fmod"
} ],
mostar_fmod: [ function(c, e) {
"use strict";
cc._RF.push(e, "3c2d7hDw9VGV4dLiFpIuKLS", "mostar_fmod");
var t = cc.Class({
statics: {
test: "event:/Music/Level 03",
zhucheng: {
event: "event:/MUSIC/music_switch",
paramer: "music switch",
value: 0
},
senlin: {
event: "event:/MUSIC/music_switch",
paramer: "music switch",
value: 2
},
bianda: "event:/SFX/jinzhandongzuo/sfx_1jinzhan_bianda",
load: function() {
cc.sys.os === cc.sys.OS_IOS ? jsb.reflection.callStaticMethod("AppController", "jsLoadBank") : cc.sys.os === cc.sys.OS_ANDROID && jsb.reflection.callStaticMethod("org/cocos2dx/javascript/AppActivity", "jsLoadBank", "()V");
},
playMusic: function(c) {
cc.sys.os === cc.sys.OS_IOS ? jsb.reflection.callStaticMethod("AppController", "jsPlayMusicEvent:andParamer:andValue:", c.event, c.paramer, c.value) : cc.sys.os === cc.sys.OS_ANDROID && jsb.reflection.callStaticMethod("org/cocos2dx/javascript/AppActivity", "jsPlayMusicEvent", "(Ljava/lang/String;Ljava/lang/String;F)V", c.event, c.paramer, c.value);
},
pauseMusic: function(c) {
cc.sys.os === cc.sys.OS_IOS ? jsb.reflection.callStaticMethod("AppController", "jsPauseMusicEvent:andParamer:andValue:", c.event, c.paramer, c.value) : cc.sys.os === cc.sys.OS_ANDROID && jsb.reflection.callStaticMethod("org/cocos2dx/javascript/AppActivity", "jsPauseMusicEvent", "(Ljava/lang/String;Ljava/lang/String;F)V", c.event, c.paramer, c.value);
},
resumeMusic: function(c) {
cc.sys.os === cc.sys.OS_IOS ? jsb.reflection.callStaticMethod("AppController", "jsResumeMusicEvent:andParamer:andValue:", c.event, c.paramer, c.value) : cc.sys.os === cc.sys.OS_ANDROID && jsb.reflection.callStaticMethod("org/cocos2dx/javascript/AppActivity", "jsResumeMusicEvent", "(Ljava/lang/String;Ljava/lang/String;F)V", c.event, c.paramer, c.value);
},
stopMusic: function(c) {
cc.sys.os === cc.sys.OS_IOS ? jsb.reflection.callStaticMethod("AppController", "jsStopMusicEvent:andParamer:andValue:", c.event, c.paramer, c.value) : cc.sys.os === cc.sys.OS_ANDROID && jsb.reflection.callStaticMethod("org/cocos2dx/javascript/AppActivity", "jsStopMusicEvent", "(Ljava/lang/String;Ljava/lang/String;F)V", c.event, c.paramer, c.value);
},
playEffect: function(c) {
cc.sys.os === cc.sys.OS_IOS ? jsb.reflection.callStaticMethod("AppController", "jsPlayEffectEvent:", c) : cc.sys.os === cc.sys.OS_ANDROID && jsb.reflection.callStaticMethod("org/cocos2dx/javascript/AppActivity", "jsPlayEffectEvent", "(Ljava/lang/String;)V", c);
}
}
});
e.exports = t;
cc._RF.pop();
}, {} ]
}, {}, [ "main", "mostar_fmod" ]);