window.__require = function t(s, c, o) {
function e(a, i) {
if (!c[a]) {
if (!s[a]) {
var r = a.split("/");
r = r[r.length - 1];
if (!s[r]) {
var l = "function" == typeof __require && __require;
if (!i && l) return l(r, !0);
if (n) return n(r, !0);
throw new Error("Cannot find module '" + a + "'");
}
a = r;
}
var p = c[a] = {
exports: {}
};
s[a][0].call(p.exports, function(t) {
return e(s[a][1][t] || t);
}, p, p.exports, t, s, c, o);
}
return c[a].exports;
}
for (var n = "function" == typeof __require && __require, a = 0; a < o.length; a++) e(o[a]);
return e;
}({
main: [ function(t, s) {
"use strict";
cc._RF.push(s, "e22a5UlHvdKqbt30vd8GrHn", "main");
var c = t("mostar_fmod");
cc.Class({
extends: cc.Component,
properties: {},
start: function() {
this.paused = !1;
c.load();
},
playAction: function() {
c.play(c.test);
},
pauseAction: function() {
this.paused = !this.paused;
this.paused ? c.pause(c.test) : c.resume(c.test);
},
stopAction: function() {
c.stop(c.test);
}
});
cc._RF.pop();
}, {
mostar_fmod: "mostar_fmod"
} ],
mostar_fmod: [ function(t, s) {
"use strict";
cc._RF.push(s, "3c2d7hDw9VGV4dLiFpIuKLS", "mostar_fmod");
var c = cc.Class({
statics: {
test: "event:/Music/Level 03",
load: function() {
cc.sys.os === cc.sys.OS_IOS ? jsb.reflection.callStaticMethod("AppController", "jsLoadBank") : cc.sys.os === cc.sys.OS_ANDROID && jsb.reflection.callStaticMethod("org/cocos2dx/javascript/AppActivity", "jsLoadBank", "()V");
},
play: function(t) {
cc.sys.os === cc.sys.OS_IOS ? jsb.reflection.callStaticMethod("AppController", "jsPlayEvent:", t) : cc.sys.os === cc.sys.OS_ANDROID && jsb.reflection.callStaticMethod("org/cocos2dx/javascript/AppActivity", "jsPlayEvent", "(Ljava/lang/String;)V", t);
},
pause: function(t) {
cc.sys.os === cc.sys.OS_IOS ? jsb.reflection.callStaticMethod("AppController", "jsPauseEvent:", t) : cc.sys.os === cc.sys.OS_ANDROID && jsb.reflection.callStaticMethod("org/cocos2dx/javascript/AppActivity", "jsPauseEvent", "(Ljava/lang/String;)V", t);
},
resume: function(t) {
cc.sys.os === cc.sys.OS_IOS ? jsb.reflection.callStaticMethod("AppController", "jsResumeEvent:", t) : cc.sys.os === cc.sys.OS_ANDROID && jsb.reflection.callStaticMethod("org/cocos2dx/javascript/AppActivity", "jsResumeEvent", "(Ljava/lang/String;)V", t);
},
stop: function(t) {
cc.sys.os === cc.sys.OS_IOS ? jsb.reflection.callStaticMethod("AppController", "jsStopEvent:", t) : cc.sys.os === cc.sys.OS_ANDROID && jsb.reflection.callStaticMethod("org/cocos2dx/javascript/AppActivity", "jsStopEvent", "(Ljava/lang/String;)V", t);
}
}
});
s.exports = c;
cc._RF.pop();
}, {} ]
}, {}, [ "main", "mostar_fmod" ]);