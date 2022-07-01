// Learn cc.Class:
//  - https://docs.cocos.com/creator/manual/en/scripting/class.html
// Learn Attribute:
//  - https://docs.cocos.com/creator/manual/en/scripting/reference/attributes.html
// Learn life-cycle callbacks:
//  - https://docs.cocos.com/creator/manual/en/scripting/life-cycle-callbacks.html

let FMOD = require('mostar_fmod');

cc.Class({
    extends: cc.Component,

    properties: {
    },

    // LIFE-CYCLE CALLBACKS:

    // onLoad () {},

    start () {
        this.paused = false;
        FMOD.load();
    },

    playAction() {
        FMOD.play(FMOD.test);
    },

    pauseAction() {
        this.paused = !this.paused;
        if (this.paused) {
            FMOD.pause(FMOD.test);
        } else {
            FMOD.resume(FMOD.test);
        }
    },

    stopAction() {
        FMOD.stop(FMOD.test)
    },

    // update (dt) {},
});
