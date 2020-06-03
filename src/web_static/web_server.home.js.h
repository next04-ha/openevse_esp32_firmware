static const char CONTENT_HOME_JS[] PROGMEM = 
  "\"use strict\";function OpenEVSEError(e){var t=1<arguments.length&&void 0!==arguments[1]?arguments[1]:\"\";this.type=e,this.message=t}function OpenEVSERequest(){var t=this;t._done=function(){},t._error=function(){},t._always=function(){},t.done=function(e){return t._done=e,t},t.error=function(e){return t._error=e,t},t.always=function(e){return t._always=e,t}}function OpenEVSE(e){var l=this;l._version=\"0.1\",l._endpoint=e,l.states={0:\"unknown\",1:\"not connected\",2:\"connected\",3:\"charging\",4:\"vent required\",5:\"diode check failed\",6:\"gfci fault\",7:\"no ground\",8:\"stuck relay\",9:\"gfci self-test failure\",10:\"over temperature\",11:\"over current\",254:\"sleeping\",255:\"disabled\"},l._lcd_colors=[\"off\",\"red\",\"green\",\"yellow\",\"blue\",\"violet\",\"teal\",\"white\"],l._status_functions={disable:\"FD\",enable:\"FE\",sleep:\"FS\"},l._lcd_types=[\"monochrome\",\"rgb\"],l._service_levels=[\"A\",\"1\",\"2\"],l.STANDARD_SERIAL_TIMEOUT=.5,l.RESET_SERIAL_TIMEOUT=10,l.STATUS_SERIAL_TIMEOUT=0,l.SYNC_SERIAL_TIMEOUT=.5,l.NEWLINE_MAX_AGE=5,l.CORRECT_RESPONSE_PREFIXES=\"$NK\",l.regex=/\\$([^^]*)(\\^..)?/,l._request=function(e){var o=1<arguments.length&&void 0!==arguments[1]?arguments[1]:function(){},t=\"$\"+(Array.isArray(e)?e.join(\"+\"):e),r=new OpenEVSERequest;return $.get(l._endpoint+\"?json=1&rapi=\"+encodeURI(t),function(e){var t=e.ret.match(l.regex);if(null!==t){var n=t[1].split(\" \");\"OK\"===n[0]?(o(n.slice(1)),r._done(n.slice(1))):r._error(new OpenEVSEError(\"OperationFailed\"))}else r._error(new OpenEVSEError(\"UnexpectedResponse\"))},\"json\").always(function(){r._always()}).fail(function(){r._error(new OpenEVSEError(\"RequestFailed\"))}),r},l._flags=function(n){var o=l._request(\"GE\",function(e){var t=parseInt(e[1],16);isNaN(t)?o._error(new OpenEVSEError(\"ParseError\",'Failed to parse \"'+e[0]+'\"')):n({service_level:1+(1&t),diode_check:0==(2&t),vent_required:0==(4&t),ground_check:0==(8&t),stuck_relay_check:0==(16&t),auto_service_level:0==(32&t),auto_start:0==(64&t),serial_debug:0!=(128&t),lcd_type:0!=(256&t)?\"monochrome\":\"rgb\",gfi_self_test:0==(512&t),temp_check:0==(1024&t)})});return o},l.reset=function(){return l._request(\"FR\")},l.time=function(u){var e=1<arguments.length&&void 0!==arguments[1]&&arguments[1];if(!1!==e)return l._request([\"S1\",e.getFullYear()-2e3,e.getMonth()+1,e.getDate(),e.getHours(),e.getMinutes(),e.getSeconds()],function(){l.time(u)});var c=l._request(\"GT\",function(e){if(6<=e.length){var t=parseInt(e[0]),n=parseInt(e[1]),o=parseInt(e[2]),r=parseInt(e[3]),a=parseInt(e[4]),i=parseInt(e[5]);if(isNaN(t)||isNaN(n)||isNaN(o)||isNaN(r)||isNaN(a)||isNaN(i))c._error(new OpenEVSEError(\"ParseError\",'Could not parse time \"'+e.join(\" \")+'\" arguments'));else if(165==t&&165==n&&165==o&&165==r&&165==a&&85==i)u(new Date(0),!1);else{var s=new Date(2e3+t,n-1,o,r,a,i);u(s,!0)}}else c._error(new OpenEVSEError(\"ParseError\",\"Only received \"+e.length+\" arguments\"))});return c},l.timer=function(a){var i=1<arguments.length&&void 0!==arguments[1]&&arguments[1],s=2<arguments.length&&void 0!==arguments[2]&&arguments[2];function u(e){return(e<10?\"0\":\"\")+e}if(!1!==i&&!1!==s){var e=/([01]\\d|2[0-3]):([0-5]\\d)/,t=i.match(e),n=s.match(e);return null!==t&&null!==n?l._request([\"ST\",parseInt(t[1]),parseInt(t[2]),parseInt(n[1]),parseInt(n[2])],function(){l.timer(a)}):!1}var c=l._request(\"GD\",function(e){if(4<=e.length){var t=parseInt(e[0]),n=parseInt(e[1]),o=parseInt(e[2]),r=parseInt(e[3]);isNaN(t)||isNaN(n)||isNaN(o)||isNaN(r)?c._error(new OpenEVSEError(\"ParseError\",'Could not parse time \"'+e.join(\" \")+'\" arguments')):0===t&&0===n&&0===o&&0===r?a(!1,\"--:--\",\"--:--\"):(i=u(t)+\":\"+u(n),s=u(o)+\":\"+u(r),a(!0,i,s))}else c._error(new OpenEVSEError(\"ParseError\",\"Only received \"+e.length+\" arguments\"))});return c},l.cancelTimer=function(e){return l._request([\"ST\",0,0,0,0],function(){e()})},l.time_limit=function(n){var e=1<arguments.length&&void 0!==arguments[1]&&arguments[1];if(!1!==e)return l._request([\"S3\",Math.round(e/15)],function(){l.time_limit(n)});var o=l._request(\"G3\",function(e){if(1<=e.length){var t=parseInt(e[0]);isNaN(t)?o._error(new OpenEVSEError(\"ParseError\",'Could not parse \"'+e.join(\" \")+'\" arguments')):n(15*t)}else o._error(new OpenEVSEError(\"ParseError\",\"Only received \"+e.length+\" arguments\"))});return o},l.charge_limit=function(n){var e=1<arguments.length&&void 0!==arguments[1]&&arguments[1];if(!1!==e)return l._request([\"SH\",e],function(){l.charge_limit(n)});var o=l._request(\"GH\",function(e){if(1<=e.length){var t=parseInt(e[0]);isNaN(t)?o._error(new OpenEVSEError(\"ParseError\",'Could not parse \"'+e.join(\" \")+'\" arguments')):n(t)}else o._error(new OpenEVSEError(\"ParseError\",\"Only received \"+e.length+\" arguments\"))});return o},l.ammeter_settings=function(o){var e=1<arguments.length&&void 0!==arguments[1]&&arguments[1],t=2<arguments.length&&void 0!==arguments[2]&&arguments[2];if(!1!==e&&!1!==t)return l._request([\"SA\",e,t],function(){o(e,t)});var r=l._request(\"GA\",function(e){if(2<=e.length){var t=parseInt(e[0]),n=parseInt(e[1]);isNaN(t)||isNaN(n)?r._error(new OpenEVSEError(\"ParseError\",'Could not parse \"'+e.join(\" \")+'\" arguments')):o(t,n)}else r._error(new OpenEVSEError(\"ParseError\",\"Only received \"+e.length+\" arguments\"))});return r},l.current_capacity=function(n){var e=1<arguments.length&&void 0!==arguments[1]&&arguments[1];if(!1!==e)return l._request([\"SC\",e],function(){l.current_capacity(n)});var o=l._request(\"GE\",function(e){if(1<=e.length){var t=parseInt(e[0]);isNaN(t)?o._error(new OpenEVSEError(\"ParseError\",'Could not parse \"'+e.join(\" \")+'\" arguments')):n(t)}else o._error(new OpenEVSEError(\"ParseError\",\"Only received \"+e.length+\" arguments\"))});return o},l.service_level=function(t){var e=1<arguments.length&&void 0!==arguments[1]&&arguments[1];return!1!==e?l._request([\"SL\",l._service_levels[e]],function(){l.service_level(t)}):l._flags(function(e){t(e.auto_service_level?0:e.service_level,e.service_level)})},l.current_capacity_range=function(o){var r=l._request(\"GC\",function(e){if(2<=e.length){var t=parseInt(e[0]),n=parseInt(e[1]);isNaN(t)||isNaN(n)?r._error(new OpenEVSEError(\"ParseError\",'Could not parse \"'+e.join(\" \")+'\" arguments')):o(t,n)}else r._error(new OpenEVSEError(\"ParseError\",\"Only received \"+e.length+\" arguments\"))});return r},l.status=function(o){var e=1<arguments.length&&void 0!==arguments[1]&&arguments[1];if(!1!==e){var t=l._status_functions[e];return l._request([t],function(){l.status(o)})}var r=l._request(\"GS\",function(e){if(1<=e.length){var t=parseInt(e[0]),n=parseInt(e[1]);isNaN(t)||isNaN(n)?r._error(new OpenEVSEError(\"ParseError\",'Could not parse \"'+e.join(\" \")+'\" arguments')):o(t,n)}else r._error(new OpenEVSEError(\"ParseError\",\"Only received \"+e.length+\" arguments\"))});return r},l.diode_check=function(t){var e=1<arguments.length&&void 0!==arguments[1]?arguments[1]:null;return null!==e?l._request([\"FF\",\"D\",e?\"1\":\"0\"],function(){l.diode_check(t)}):l._flags(function(e){t(e.diode_check)})},l.gfi_self_test=function(t){var e=1<arguments.length&&void 0!==arguments[1]?arguments[1]:null;return null!==e?l._request([\"FF F\",e?\"1\":\"0\"],function(){l.gfi_self_test(t)}):l._flags(function(e){t(e.gfi_self_test)})},l.ground_check=function(t){var e=1<arguments.length&&void 0!==arguments[1]?arguments[1]:null;return null!==e?l._request([\"FF G\",e?\"1\":\"0\"],function(){l.ground_check(t)}):l._flags(function(e){t(e.ground_check)})},l.stuck_relay_check=function(t){var e=1<arguments.length&&void 0!==arguments[1]?arguments[1]:null;return null!==e?l._request([\"FF R\",e?\"1\":\"0\"],function(){l.stuck_relay_check(t)}):l._flags(function(e){t(e.stuck_relay_check)})},l.vent_required=function(t){var e=1<arguments.length&&void 0!==arguments[1]?arguments[1]:null;return null!==e?l._request([\"FF V\",e?\"1\":\"0\"],function(){l.vent_required(t)}):l._flags(function(e){t(e.vent_required)})},l.temp_check=function(t){var e=1<arguments.length&&void 0!==arguments[1]?arguments[1]:null;return null!==e?l._request([\"FF T\",e?\"1\":\"0\"],function(){l.temp_check(t)}):l._flags(function(e){t(e.temp_check)})},l.over_temperature_thresholds=function(o){var e=1<arguments.length&&void 0!==arguments[1]&&arguments[1],t=2<arguments.length&&void 0!==arguments[2]&&arguments[2];if(!1!==e&&!1!==t)return l._request([\"SO\",e,t],function(){l.over_temperature_thresholds(o)});var r=l._request(\"GO\",function(e){if(2<=e.length){var t=parseInt(e[0]),n=parseInt(e[1]);isNaN(t)||isNaN(n)?r._error(new OpenEVSEError(\"ParseError\",'Could not parse \"'+e.join(\" \")+'\" arguments')):o(t,n)}else r._error(new OpenEVSEError(\"ParseError\",\"Only received \"+e.length+\" arguments\"))});return r},l.press_button=function(e){return l._request(\"F1\",function(){e()})},l.setEndpoint=function(e){l._endpoint=e}}function RapiViewModel(e){var t=this;t.baseEndpoint=e,t.rapiSend=ko.observable(!1),t.cmd=ko.observable(\"\"),t.ret=ko.observable(\"\"),t.send=function(){t.rapiSend(!0),$.get(t.baseEndpoint()+\"/r?json=1&rapi=\"+encodeURI(t.cmd()),function(e){t.ret(\">\"+e.ret),t.cmd(e.cmd)},\"json\").always(function(){t.rapiSend(!1)})}}function TimeViewModel(n){var o=this;function r(e){return(e<10?\"0\":\"\")+e}o.evseTimedate=ko.observable(new Date),o.localTimedate=ko.observable(new Date),o.nowTimedate=ko.observable(null),o.hasRTC=ko.observable(!0),o.elapsedNow=ko.observable(new Date(0)),o.elapsedLocal=ko.observable(new Date),o.divertUpdateNow=ko.observable(new Date(0)),o.divertUpdateLocal=ko.observable(new Date),o.date=ko.pureComputed({read:function(){if(null===o.nowTimedate())return\"\";var e=o.nowTimedate();return e.getFullYear()+\"-\"+r(e.getMonth()+1)+\"-\"+r(e.getDate())},write:function(e){var t=o.evseTimedate();e+=\" \"+r(t.getHours())+\":\"+r(t.getMinutes())+\":\"+r(t.getSeconds()),o.evseTimedate(new Date(e)),o.localTimedate(new Date)}}),o.time=ko.pureComputed({read:function(){if(null===o.nowTimedate())return\"--:--:--\";var e=o.nowTimedate();return r(e.getHours())+\":\"+r(e.getMinutes())+\":\"+r(e.getSeconds())},write:function(e){var t=e.split(\":\"),n=o.evseTimedate();n.setHours(parseInt(t[0])),n.setMinutes(parseInt(t[1])),o.evseTimedate(n),o.localTimedate(new Date)}}),o.elapsed=ko.pureComputed(function(){if(null===o.nowTimedate())return\"0:00:00\";var e=o.elapsedNow().getTime(),t=(e=Math.floor(e/1e3))%60,n=(e=Math.floor(e/60))%60;return Math.floor(e/60)+\":\"+r(n)+\":\"+r(t)}),n.status.elapsed.subscribe(function(e){o.elapsedNow(new Date(1e3*e)),o.elapsedLocal(new Date)}),o.divert_update=ko.pureComputed(function(){if(null===o.nowTimedate())return!1;var e=o.divertUpdateNow().getTime();return Math.floor(e/1e3)}),n.status.divert_update.subscribe(function(e){o.divertUpdateNow(new Date(1e3*e)),o.divertUpdateLocal(new Date)});var a=null;o.automaticTime=ko.observable(!0),o.timeUpdate=function(e){var t=!(1<arguments.length&&void 0!==arguments[1])||arguments[1];o.hasRTC(t),null!==a&&(clearInterval(a),a=null),o.evseTimedate(e),o.nowTimedate(e),o.localTimedate(new Date),a=setInterval(function(){o.automaticTime()&&o.nowTimedate(new Date(o.evseTimedate().getTime()+(new Date-o.localTimedate()))),n.isCharging()&&o.elapsedNow(new Date(1e3*n.status.elapsed()+(new Date-o.elapsedLocal()))),o.divertUpdateNow(new Date(1e3*n.status.divert_update()+(new Date-o.divertUpdateLocal())))},1e3)}}function TimeZoneViewModel(e){this.name=ko.observable(e.name),this.value=ko.observable(e.name+\"|\"+e.tz)}function ZonesViewModel(e){var o=this,t=ko.pureComputed(function(){return e()+\"/zones.json\"});o.fetching=ko.observable(!1),o.zones=ko.mapping.fromJS([],{key:function(e){return ko.utils.unwrapObservable(e.name)},create:function(e){return new TimeZoneViewModel(e.data)}}),o.initialValue=function(e){var t=e.split(\"|\",2);2==t.length?o.zones.push(new TimeZoneViewModel({name:t[0],tz:t[1]})):o.zones.push(new TimeZoneViewModel({name:\"Default\",tz:t[1]}))},o.update=function(){var e=0<arguments.length&&void 0!==arguments[0]?arguments[0]:function(){};o.fetching(!0),$.get(t(),function(e){var t=[];for(var n in e)e.hasOwnProperty(n)&&t.push({name:n,tz:e[n]});ko.mapping.fromJS(t,o.zones)},\"json\").always(function(){o.fetching(!1),e()})}}function DummyRequest(){var t=this;t.always=function(e){return e(),t}}function OpenEvseViewModel(e,t){var r=this,n=ko.pureComputed(function(){return e()+\"/r\"});r.openevse=new OpenEVSE(n()),n.subscribe(function(e){r.openevse.setEndpoint(e)}),r.status=t,r.time=new TimeViewModel(r),r.serviceLevels=[{name:\"Auto\",value:0},{name:\"1\",value:1},{name:\"2\",value:2}],r.currentLevels=ko.observableArray([]),r.timeLimits=[{name:\"none\",value:0},{name:\"15 min\",value:15},{name:\"30 min\",value:30},{name:\"45 min\",value:45},{name:\"1 hour\",value:60},{name:\"1.5 hours\",value:90},{name:\"2 hours\",value:120},{name:\"2.5 hours\",value:150},{name:\"3 hours\",value:180},{name:\"4 hours\",value:240},{name:\"5 hours\",value:300},{name:\"6 hours\",value:360},{name:\"7 hours\",value:420},{name:\"8 hours\",value:480}],r.chargeLimits=[{name:\"none\",value:0},{name:\"1 kWh\",value:1},{name:\"2 kWh\",value:2},{name:\"3 kWh\",value:3},{name:\"4 kWh\",value:4},{name:\"5 kWh\",value:5},{name:\"6 kWh\",value:6},{name:\"7 kWh\",value:7},{name:\"8 kWh\",value:8},{name:\"9 kWh\",value:9},{name:\"10 kWh\",value:10},{name:\"15 kWh\",value:11},{name:\"20 kWh\",value:12},{name:\"25 kWh\",value:25},{name:\"30 kWh\",value:30},{name:\"35 kWh\",value:35},{name:\"40 kWh\",value:40},{name:\"45 kWh\",value:45},{name:\"50 kWh\",value:50},{name:\"55 kWh\",value:55},{name:\"60 kWh\",value:60},{name:\"70 kWh\",value:70},{name:\"80 kWh\",value:80},{name:\"90 kWh\",value:90}],r.serviceLevel=ko.observable(-1),r.actualServiceLevel=ko.observable(-1),r.minCurrentLevel=ko.observable(-1),r.maxCurrentLevel=ko.observable(-1),r.currentCapacity=ko.observable(-1),r.timeLimit=ko.observable(-1),r.chargeLimit=ko.observable(-1),r.delayTimerEnabled=ko.observable(!1),r.delayTimerStart=ko.observable(\"--:--\"),r.delayTimerStop=ko.observable(\"--:--\"),r.gfiSelfTestEnabled=ko.observable(!1),r.groundCheckEnabled=ko.observable(!1),r.stuckRelayEnabled=ko.observable(!1),r.tempCheckEnabled=ko.observable(!1),r.diodeCheckEnabled=ko.observable(!1),r.ventRequiredEnabled=ko.observable(!1),r.allTestsEnabled=ko.pureComputed(function(){return r.gfiSelfTestEnabled()&&r.groundCheckEnabled()&&r.stuckRelayEnabled()&&r.tempCheckEnabled()&&r.diodeCheckEnabled()&&r.ventRequiredEnabled()}),r.tempCheckSupported=ko.observable(!1),r.isConnected=ko.pureComputed(function(){return-1!==[2,3].indexOf(r.status.state())}),r.isReady=ko.pureComputed(function(){return-1!==[0,1].indexOf(r.status.state())}),r.isCharging=ko.pureComputed(function(){return 3===r.status.state()}),r.isError=ko.pureComputed(function(){return-1!==[4,5,6,7,8,9,10,11].indexOf(r.status.state())}),r.isEnabled=ko.pureComputed(function(){return-1!==[0,1,2,3].indexOf(r.status.state())}),r.isSleeping=ko.pureComputed(function(){return 254===r.status.state()}),r.isDisabled=ko.pureComputed(function(){return 255===r.status.state()}),r.selectTimeLimit=function(e){if(r.timeLimit()!==e)for(var t=0;t<r.timeLimits.length;t++){var n=r.timeLimits[t];if(n.value>=e){r.timeLimit(n.value);break}}},r.selectChargeLimit=function(e){if(r.chargeLimit()!==e)for(var t=0;t<r.chargeLimits.length;t++){var n=r.chargeLimits[t];if(n.value>=e){r.chargeLimit(n.value);break}}};var o=[function(){return!1===r.status.time()?r.openevse.time(r.time.timeUpdate):new DummyRequest},function(){return r.openevse.service_level(function(e,t){r.serviceLevel(e),r.actualServiceLevel(t)})},function(){return r.updateCurrentCapacity()},function(){return r.openevse.current_capacity(function(e){r.currentCapacity(e)})},function(){return r.openevse.time_limit(function(e){r.selectTimeLimit(e)})},function(){return r.openevse.charge_limit(function(e){r.selectChargeLimit(e)})},function(){return r.openevse.gfi_self_test(function(e){r.gfiSelfTestEnabled(e)})},function(){return r.openevse.ground_check(function(e){r.groundCheckEnabled(e)})},function(){return r.openevse.stuck_relay_check(function(e){r.stuckRelayEnabled(e)})},function(){return r.openevse.temp_check(function(e){r.tempCheckEnabled(e)})},function(){return r.openevse.diode_check(function(e){r.diodeCheckEnabled(e)})},function(){return r.openevse.vent_required(function(e){r.ventRequiredEnabled(e)})},function(){return r.openevse.temp_check(function(){r.tempCheckSupported(!0)},r.tempCheckEnabled()).error(function(){r.tempCheckSupported(!1)})},function(){return r.openevse.timer(function(e,t,n){r.delayTimerEnabled(e),r.delayTimerStart(t),r.delayTimerStop(n)})}];r.updateCount=ko.observable(0),r.updateTotal=ko.observable(o.length),r.updateCurrentCapacity=function(){return r.openevse.current_capacity_range(function(e,t){r.minCurrentLevel(e),r.maxCurrentLevel(t);var n=r.currentCapacity();r.currentLevels.removeAll();for(var o=r.minCurrentLevel();o<=r.maxCurrentLevel();o++)r.currentLevels.push({name:o+\" A\",value:o});r.currentCapacity(n)})},r.updatingServiceLevel=ko.observable(!1),r.savedServiceLevel=ko.observable(!1),r.updatingCurrentCapacity=ko.observable(!1),r.savedCurrentCapacity=ko.observable(!1),r.updatingTimeLimit=ko.observable(!1),r.savedTimeLimit=ko.observable(!1),r.updatingChargeLimit=ko.observable(!1),r.savedChargeLimit=ko.observable(!1),r.updatingDelayTimer=ko.observable(!1),r.savedDelayTimer=ko.observable(!1),r.updatingStatus=ko.observable(!1),r.savedStatus=ko.observable(!1),r.updatingGfiSelfTestEnabled=ko.observable(!1),r.savedGfiSelfTestEnabled=ko.observable(!1),r.updatingGroundCheckEnabled=ko.observable(!1),r.savedGroundCheckEnabled=ko.observable(!1),r.updatingStuckRelayEnabled=ko.observable(!1),r.savedStuckRelayEnabled=ko.observable(!1),r.updatingTempCheckEnabled=ko.observable(!1),r.savedTempCheckEnabled=ko.observable(!1),r.updatingDiodeCheckEnabled=ko.observable(!1),r.savedDiodeCheckEnabled=ko.observable(!1),r.updatingVentRequiredEnabled=ko.observable(!1),r.savedVentRequiredEnabled=ko.observable(!1);var a=!(r.setForTime=function(e,t){e(!0),setTimeout(function(){e(!1)},t)});function i(e){return/([01]\\d|2[0-3]):([0-5]\\d)/.test(e)}r.subscribe=function(){a||(r.serviceLevel.subscribe(function(e){r.updatingServiceLevel(!0),r.openevse.service_level(function(e,t){r.setForTime(r.savedServiceLevel,2e3),r.actualServiceLevel(t),r.updateCurrentCapacity().always(function(){})},e).always(function(){r.updatingServiceLevel(!1)})}),r.currentCapacity.subscribe(function(t){!0!==r.updatingServiceLevel()&&(r.updatingCurrentCapacity(!0),r.openevse.current_capacity(function(e){r.setForTime(r.savedCurrentCapacity,2e3),t!==e&&r.currentCapacity(e)},t).always(function(){r.updatingCurrentCapacity(!1)}))}),r.timeLimit.subscribe(function(t){r.updatingTimeLimit(!0),r.openevse.time_limit(function(e){r.setForTime(r.savedTimeLimit,2e3),t!==e&&r.selectTimeLimit(e)},t).always(function(){r.updatingTimeLimit(!1)})}),r.chargeLimit.subscribe(function(t){r.updatingChargeLimit(!0),r.openevse.charge_limit(function(e){r.setForTime(r.savedChargeLimit,2e3),t!==e&&r.selectChargeLimit(e)},t).always(function(){r.updatingChargeLimit(!1)})}),r.gfiSelfTestEnabled.subscribe(function(t){r.updatingGfiSelfTestEnabled(!0),r.openevse.gfi_self_test(function(e){r.setForTime(r.savedGfiSelfTestEnabled,2e3),t!==e&&r.gfiSelfTestEnabled(e)},t).always(function(){r.updatingGfiSelfTestEnabled(!1)})}),r.groundCheckEnabled.subscribe(function(t){r.updatingGroundCheckEnabled(!0),r.openevse.ground_check(function(e){r.setForTime(r.savedGroundCheckEnabled,2e3),t!==e&&r.groundCheckEnabled(e)},t).always(function(){r.updatingGroundCheckEnabled(!1)})}),r.stuckRelayEnabled.subscribe(function(t){r.updatingStuckRelayEnabled(!0),r.savedStuckRelayEnabled(!1),r.openevse.stuck_relay_check(function(e){r.savedStuckRelayEnabled(!0),setTimeout(function(){r.savedStuckRelayEnabled(!1)},2e3),t!==e&&r.stuckRelayEnabled(e)},t).always(function(){r.updatingStuckRelayEnabled(!1)})}),r.tempCheckEnabled.subscribe(function(t){r.updatingTempCheckEnabled(!0),r.openevse.temp_check(function(e){r.setForTime(r.savedTempCheckEnabled,2e3),t!==e&&r.tempCheckEnabled(e)},t).always(function(){r.updatingTempCheckEnabled(!1)})}),r.diodeCheckEnabled.subscribe(function(t){r.updatingDiodeCheckEnabled(!0),r.openevse.diode_check(function(e){r.setForTime(r.savedDiodeCheckEnabled,2e3),t!==e&&r.diodeCheckEnabled(e)},t).always(function(){r.updatingDiodeCheckEnabled(!1)})}),r.ventRequiredEnabled.subscribe(function(t){r.updatingVentRequiredEnabled(!0),r.openevse.vent_required(function(e){r.setForTime(r.savedVentRequiredEnabled,2e3),t!==e&&r.ventRequiredEnabled(e)},t).always(function(){r.updatingVentRequiredEnabled(!1)})}),a=!0)},r.update=function(){var e=0<arguments.length&&void 0!==arguments[0]?arguments[0]:function(){};r.updateCount(0),r.nextUpdate(e)},r.nextUpdate=function(e){(0,o[r.updateCount()])().always(function(){r.updateCount(r.updateCount()+1),r.updateCount()<o.length?r.nextUpdate(e):(r.subscribe(),e())})},r.delayTimerValid=ko.pureComputed(function(){return i(r.delayTimerStart())&&i(r.delayTimerStop())}),r.startDelayTimer=function(){r.updatingDelayTimer(!0),r.openevse.timer(function(){r.delayTimerEnabled(!0)},r.delayTimerStart(),r.delayTimerStop()).always(function(){r.updatingDelayTimer(!1)})},r.stopDelayTimer=function(){r.updatingDelayTimer(!0),r.openevse.cancelTimer(function(){r.delayTimerEnabled(!1)}).always(function(){r.updatingDelayTimer(!1)})},r.setStatus=function(e){var t=r.status.state();\"disabled\"===e&&255===t||\"sleep\"===e&&254===t||\"enable\"===e&&t<254||(r.updatingStatus(!0),!r.delayTimerEnabled()||\"sleep\"!==e&&\"enable\"!==e?r.openevse.status(function(e){r.status.state(e)},e).always(function(){r.updatingStatus(!1)}):r.openevse.press_button(function(){e=!1}).always(function(){r.openevse.status(function(e){r.status.state(e)},e).always(function(){r.updatingStatus(!1)})}))},r.restartFetching=ko.observable(!1),r.restart=function(){confirm(\"Restart OpenEVSE? Current config will be saved, takes approximately 10s.\")&&(r.restartFetching(!0),r.openevse.reset().always(function(){r.restartFetching(!1)}))}}function OpenEvseWiFiViewModel(e,t,n){var r=this;r.baseHost=ko.observable(\"\"!==e?e:\"openevse.local\"),r.basePort=ko.observable(t),r.baseProtocol=ko.observable(n),r.baseEndpoint=ko.pureComputed(function(){var e=\"//\"+r.baseHost();return 80!==r.basePort()&&(e+=\":\"+r.basePort()),e}),r.wsEndpoint=ko.pureComputed(function(){var e=\"ws://\"+r.baseHost();return\"https:\"===r.baseProtocol()&&(e=\"wss://\"+r.baseHost()),80!==r.basePort()&&(e+=\":\"+r.basePort()),e+=\"/ws\"}),r.config=new ConfigViewModel(r.baseEndpoint),r.status=new StatusViewModel(r.baseEndpoint),r.rapi=new RapiViewModel(r.baseEndpoint),r.scan=new WiFiScanViewModel(r.baseEndpoint),r.wifi=new WiFiConfigViewModel(r.baseEndpoint,r.config,r.status,r.scan),r.openevse=new OpenEvseViewModel(r.baseEndpoint,r.status),r.zones=new ZonesViewModel(r.baseEndpoint),r.initialised=ko.observable(!1),r.updating=ko.observable(!1),r.scanUpdating=ko.observable(!1),r.wifi.selectedNet.subscribe(function(e){!1!==e&&r.config.ssid(e.ssid())}),r.config.ssid.subscribe(function(e){r.wifi.setSsid(e)}),r.showMqttInfo=ko.observable(!1),r.showSolarDivert=ko.observable(!1),r.showSafety=ko.observable(!1),r.toggle=function(e){e(!e())},r.advancedMode=ko.observable(!1),r.advancedMode.subscribe(function(e){r.setCookie(\"advancedMode\",e.toString())}),r.developerMode=ko.observable(!1),r.developerMode.subscribe(function(e){r.setCookie(\"developerMode\",e.toString()),e&&r.advancedMode(!0)});var o=null,a=null;r.status.time.subscribe(function(e){r.openevse.time.timeUpdate(new Date(e))}),r.timeSource=ko.computed({read:function(){return r.config.sntp_enabled()?\"ntp\":r.openevse.time.automaticTime()?\"browser\":\"manual\"},write:function(e){switch(e){case\"ntp\":r.config.sntp_enabled(!0),r.openevse.time.automaticTime(!0);break;case\"browser\":r.config.sntp_enabled(!1),r.openevse.time.automaticTime(!0);break;case\"manual\":r.config.sntp_enabled(!1),r.openevse.time.automaticTime(!1)}}}),r.time_zone=ko.computed({read:function(){return r.config.time_zone()},write:function(e){void 0!==e&&!1===r.zones.fetching()&&r.config.time_zone(e)}});var i=\"status\";function s(){var e=r.config.emoncms_server().split(\"://\",2);return 1<e.length?e:[r.config.http_supported_protocols()[0],e[0]]}\"\"!==window.location.hash&&(i=window.location.hash.substr(1)),r.tab=ko.observable(i),r.tab.subscribe(function(e){window.location.hash=\"#\"+e}),r.isSystem=ko.pureComputed(function(){return\"system\"===r.tab()}),r.isServices=ko.pureComputed(function(){return\"services\"===r.tab()}),r.isStatus=ko.pureComputed(function(){return\"status\"===r.tab()}),r.isRapi=ko.pureComputed(function(){return\"rapi\"===r.tab()}),r.upgradeUrl=ko.observable(\"about:blank\"),r.wifiPassword=new PasswordViewModel(r.config.pass),r.emoncmsApiKey=new PasswordViewModel(r.config.emoncms_apikey),r.mqttPassword=new PasswordViewModel(r.config.mqtt_pass),r.wwwPassword=new PasswordViewModel(r.config.www_password),r.emoncms_protocol=ko.computed({read:function(){return 0==r.config.http_supported_protocols().length?\"\":s()[0]},write:function(e){0<r.config.http_supported_protocols().length&&r.config.emoncms_server(e+\"://\"+s()[1])}}),r.emoncms_server=ko.computed({read:function(){return 0==r.config.http_supported_protocols().length?r.config.emoncms_server():s()[1]},write:function(e){if(0<r.config.http_supported_protocols().length){var t=e.split(\"://\",2),n=1<t.length?t[0]:s()[0],o=1<t.length?t[1]:e;r.config.emoncms_server(n+\"://\"+o)}else r.config.emoncms_server()}}),r.config.mqtt_protocol.subscribe(function(e){switch(e){case\"mqtt\":\"8883\"==r.config.mqtt_port()&&r.config.mqtt_port(\"1883\");break;case\"mqtts\":\"1883\"==r.config.mqtt_port()&&r.config.mqtt_port(\"8883\")}}),r.loadedCount=ko.observable(0),r.itemsLoaded=ko.pureComputed(function(){return r.loadedCount()+r.openevse.updateCount()}),r.itemsTotal=ko.observable(2+r.openevse.updateTotal()),r.start=function(){r.updating(!0),r.status.update(function(){r.loadedCount(r.loadedCount()+1),r.config.update(function(){r.loadedCount(r.loadedCount()+1),r.baseHost().endsWith(\".local\")&&\"\"!==r.status.ipaddress()&&(\"\"===r.config.www_username()?r.baseHost(r.status.ipaddress()):window.location.replace(\"http://\"+r.status.ipaddress()+\":\"+r.basePort())),r.status.rapi_connected()?r.openevse.update(r.finishedStarting):(r.finishedStarting(),r.status.rapi_connected.subscribe(function(e){e&&r.config.update(function(){r.openevse.update(function(){})})}))}),r.connect()}),r.advancedMode(\"true\"===r.getCookie(\"advancedMode\",\"false\")),r.developerMode(\"true\"===r.getCookie(\"developerMode\",\"false\"))},r.finishedStarting=function(){r.initialised(!0),o=setTimeout(r.update,5e3),r.upgradeUrl(r.baseEndpoint()+\"/update\");for(var e=document.getElementsByTagName(\"img\"),t=0;t<e.length;t++)e[t].getAttribute(\"data-src\")&&e[t].setAttribute(\"src\",e[t].getAttribute(\"data-src\"));!1!==r.config.time_zone()&&(r.zones.initialValue(r.config.time_zone()),r.zones.update(function(){r.config.time_zone.valueHasMutated()})),r.updating(!1)};var u=!(r.update=function(){r.updating()||(r.updating(!0),null!==o&&(clearTimeout(o),o=null),r.status.update(function(){o=setTimeout(r.update,5e3),r.updating(!1)}))});r.startScan=function(){r.scanUpdating()||(u=!0,r.scanUpdating(!0),null!==a&&(clearTimeout(a),a=null),r.scan.update(function(){u&&(a=setTimeout(r.startScan,3e3)),r.scanUpdating(!1)}))},r.stopScan=function(){u=!1,r.scanUpdating()||null!==a&&(clearTimeout(a),a=null)},r.wifiConnecting=ko.observable(!1),r.status.mode.subscribe(function(e){\"STA+AP\"!==e&&\"STA\"!==e||r.wifiConnecting(!1),\"STA+AP\"===e||\"AP\"===e?r.startScan():r.stopScan()}),r.saveNetworkFetching=ko.observable(!1),r.saveNetworkSuccess=ko.observable(!1),r.saveNetwork=function(){\"\"===r.config.ssid()?alert(\"Please select network\"):(r.saveNetworkFetching(!0),r.saveNetworkSuccess(!1),$.post(r.baseEndpoint()+\"/savenetwork\",{ssid:r.config.ssid(),pass:r.config.pass()},function(){r.saveNetworkSuccess(!0),r.wifiConnecting(!0)}).fail(function(){alert(\"Failed to save WiFi config\")}).always(function(){r.saveNetworkFetching(!1)}))},r.saveAdminFetching=ko.observable(!1),r.saveAdminSuccess=ko.observable(!1),r.saveAdmin=function(){r.saveAdminFetching(!0),r.saveAdminSuccess(!1),$.post(r.baseEndpoint()+\"/saveadmin\",{user:r.config.www_username(),pass:r.config.www_password()},function(){r.saveAdminSuccess(!0)}).fail(function(){alert(\"Failed to save Admin config\")}).always(function(){r.saveAdminFetching(!1)})},r.advancedGroup=new ConfigGroupViewModel(r.baseEndpoint,function(){return{hostname:r.config.hostname(),sntp_hostname:r.config.sntp_hostname()}}).done(function(){confirm(\"These changes require a reboot to take effect. Reboot now?\")&&$.post(r.baseEndpoint()+\"/restart\",{},function(){setTimeout(function(){var e=\"http://\"+r.config.hostname()+\".local\";80!=r.basePort()&&(e+=\":\"+r.basePort()),e+=\"/\",window.location.replace(e)},5e3)}).fail(function(){alert(\"Failed to restart\")})}),r.saveEmonCmsFetching=ko.observable(!1),r.saveEmonCmsSuccess=ko.observable(!1),r.saveEmonCms=function(){var e={enable:r.config.emoncms_enabled(),server:r.config.emoncms_server(),apikey:r.config.emoncms_apikey(),node:r.config.emoncms_node(),fingerprint:r.config.emoncms_fingerprint()};!e.enable||\"\"!==e.server&&\"\"!==e.node?e.enable&&32!==e.apikey.length&&!r.emoncmsApiKey.isDummy()?alert(\"Please enter valid Emoncms apikey\"):e.enable&&\"\"!==e.fingerprint&&59!==e.fingerprint.length?alert(\"Please enter valid SSL SHA-1 fingerprint\"):(r.saveEmonCmsFetching(!0),r.saveEmonCmsSuccess(!1),$.post(r.baseEndpoint()+\"/saveemoncms\",e,function(){r.saveEmonCmsSuccess(!0)}).fail(function(){alert(\"Failed to save Admin config\")}).always(function(){r.saveEmonCmsFetching(!1)})):alert(\"Please enter Emoncms server and node\")},r.mqttGroup=new ConfigGroupViewModel(r.baseEndpoint,function(){return{mqtt_enabled:r.config.mqtt_enabled(),divert_enabled:r.config.divert_enabled(),mqtt_protocol:r.config.mqtt_protocol(),mqtt_server:r.config.mqtt_server(),mqtt_port:r.config.mqtt_port(),mqtt_reject_unauthorized:r.config.mqtt_reject_unauthorized(),mqtt_topic:r.config.mqtt_topic(),mqtt_user:r.config.mqtt_user(),mqtt_pass:r.config.mqtt_pass(),mqtt_vrms:r.config.mqtt_vrms()}}).validate(function(e){return r.config.mqtt_enabled()||r.config.divert_enabled(!1),!e.mqtt_enabled||\"\"!==e.mqtt_server||(alert(\"Please enter MQTT server\"),!1)}),r.divertGroup=new ConfigGroupViewModel(r.baseEndpoint,function(){return{divert_enabled:r.config.divert_enabled(),mqtt_solar:r.config.mqtt_solar(),mqtt_grid_ie:r.config.mqtt_grid_ie(),divert_attack_smoothing_factor:r.config.divert_attack_smoothing_factor(),divert_decay_smoothing_factor:r.config.divert_decay_smoothing_factor(),divert_min_charge_time:r.config.divert_min_charge_time()}}).validate(function(e){return!e.divert_enabled||\"\"!==e.mqtt_solar||\"\"!==e.mqtt_grid_ie||(alert(\"Please enter either a Solar PV or Grid I/E feed\"),!1)}),r.chargeMode=new ConfigGroupViewModel(r.baseEndpoint,function(){return{charge_mode:r.config.charge_mode()}}),r.isEcoModeAvailable=ko.pureComputed(function(){return r.config.mqtt_enabled()&&(\"\"!==r.config.mqtt_solar()||\"\"!==r.config.mqtt_grid_ie())}),r.ecoMode=ko.pureComputed({read:function(){return\"eco\"===r.config.charge_mode()},write:function(e){r.config.charge_mode(e&&r.config.divert_enabled()?\"eco\":\"fast\"),r.chargeMode.save()}}),r.status.divertmode.subscribe(function(e){switch(e){case 1:r.config.charge_mode(\"fast\");break;case 2:r.config.charge_mode(\"eco\")}}),r.haveSolar=ko.pureComputed(function(){return\"\"!==r.config.mqtt_solar()}),r.haveGridIe=ko.pureComputed(function(){return\"\"!==r.config.mqtt_grid_ie()}),r._divertFeedType=\"grid_ie\",r.divertFeedType=ko.computed({read:function(){var e=r.haveSolar()?\"solar\":r.haveGridIe()?\"grid_ie\":r._divertFeedType;return r._divertFeedType=e},write:function(e){\"solar\"===e&&r.haveGridIe()?(r.config.mqtt_solar(r.config.mqtt_grid_ie()),r.config.mqtt_grid_ie(\"\")):\"grid_ie\"===e&&r.haveSolar()&&(r.config.mqtt_grid_ie(r.config.mqtt_solar()),r.config.mqtt_solar(\"\")),r._divertFeedType=e}}),r.divertFeedValue=ko.computed({read:function(){return\"solar\"===r.divertFeedType()?r.config.mqtt_solar():r.config.mqtt_grid_ie()},write:function(e){\"solar\"===r.divertFeedType()?r.config.mqtt_solar(e):r.config.mqtt_grid_ie(e)}}),r.saveOhmKeyFetching=ko.observable(!1),r.saveOhmKeySuccess=ko.observable(!1),r.saveOhmKey=function(){r.saveOhmKeyFetching(!0),r.saveOhmKeySuccess(!1),$.post(r.baseEndpoint()+\"/saveohmkey\",{enable:r.config.ohm_enabled(),ohm:r.config.ohmkey()},function(){r.saveOhmKeySuccess(!0)}).fail(function(){alert(\"Failed to save Ohm key config\")}).always(function(){r.saveOhmKeyFetching(!1)})},r.setTimeFetching=ko.observable(!1),r.setTimeSuccess=ko.observable(!1),r.setTime=function(){r.setTimeFetching(!0),r.setTimeSuccess(!1);var e=r.openevse.time.automaticTime()?new Date:r.openevse.time.evseTimedate();if(0==r.status.time())r.openevse.openevse.time(function(e){var t=!(1<arguments.length&&void 0!==arguments[1])||arguments[1];r.setTimeFetching(!1),r.setTimeSuccess(t),r.openevse.time.timeUpdate(e,t)},e);else{var t=r.config.sntp_enabled(),n={ntp:t,tz:r.time_zone()};!1===t&&(n.time=e.toISOString()),$.post(r.baseEndpoint()+\"/settime\",n,function(){r.setTimeFetching(!1),r.setTimeSuccess(!0)}).fail(function(){alert(\"Failed to set time\"),r.setTimeFetching(!1)})}},r.turnOffAccessPointFetching=ko.observable(!1),r.turnOffAccessPointSuccess=ko.observable(!1),r.turnOffAccessPoint=function(){r.turnOffAccessPointFetching(!0),r.turnOffAccessPointSuccess(!1),$.post(r.baseEndpoint()+\"/apoff\",{},function(e){console.log(e),\"\"!==r.status.ipaddress()?setTimeout(function(){window.location=\"http://\"+r.status.ipaddress(),r.turnOffAccessPointSuccess(!0)},3e3):r.turnOffAccessPointSuccess(!0)}).fail(function(){alert(\"Failed to turn off Access Point\")}).always(function(){r.turnOffAccessPointFetching(!1)})},r.factoryResetFetching=ko.observable(!1),r.factoryResetSuccess=ko.observable(!1),r.factoryReset=function(){confirm(\"CAUTION: Do you really want to Factory Reset? All setting and config will be lost.\")&&(r.factoryResetFetching(!0),r.factoryResetSuccess(!1),$.post(r.baseEndpoint()+\"/reset\",{},function(){r.factoryResetSuccess(!0)}).fail(function(){alert(\"Failed to Factory Reset\")}).always(function(){r.factoryResetFetching(!1)}))},r.restartFetching=ko.observable(!1),r.restartSuccess=ko.observable(!1),r.restart=function(){confirm(\"Restart OpenEVSE WiFi? Current config will be saved, takes approximately 10s.\")&&(r.restartFetching(!0),r.restartSuccess(!1),$.post(r.baseEndpoint()+\"/restart\",{},function(){r.restartSuccess(!0)}).fail(function(){alert(\"Failed to restart\")}).always(function(){r.restartFetching(!1)}))},r.updateFetching=ko.observable(!1),r.updateComplete=ko.observable(!1),r.updateError=ko.observable(\"\"),r.updateFilename=ko.observable(\"\"),r.updateLoaded=ko.observable(0),r.updateTotal=ko.observable(1),r.updateProgress=ko.pureComputed(function(){return r.updateLoaded()/r.updateTotal()*100}),r.otaUpdate=function(){if(\"\"!==r.updateFilename()){r.updateFetching(!0),r.updateError(\"\");var e=$(\"#upload_form\")[0],t=new FormData(e);$.ajax({url:\"/update\",type:\"POST\",data:t,contentType:!1,processData:!1,xhr:function(){var e=new window.XMLHttpRequest;return e.upload.addEventListener(\"progress\",function(e){e.lengthComputable&&(r.updateLoaded(e.loaded),r.updateTotal(e.total))},!1),e}}).done(function(e){console.log(e),\"OK\"==e?r.updateComplete(!0):r.updateError(e)}).fail(function(){r.updateError(\"HTTP Update failed\")}).always(function(){r.updateFetching(!1)})}else r.updateError(\"Filename not set\")},r.pingInterval=!1,r.reconnectInterval=!1,r.socket=!1,r.connect=function(){r.socket=new WebSocket(r.wsEndpoint()),r.socket.onopen=function(e){console.log(e),r.pingInterval=setInterval(function(){r.socket.send('{\"ping\":1}')},1e3)},r.socket.onclose=function(e){console.log(e),r.reconnect()},r.socket.onmessage=function(e){console.log(e),ko.mapping.fromJSON(e.data,r.status)},r.socket.onerror=function(e){console.log(e),r.socket.close(),r.reconnect()}},r.reconnect=function(){!1!==r.pingInterval&&(clearInterval(r.pingInterval),r.pingInterval=!1),!1===r.reconnectInterval&&(r.reconnectInterval=setTimeout(function(){r.reconnectInterval=!1,r.connect()},500))},r.setCookie=function(e,t){var n=2<arguments.length&&void 0!==arguments[2]&&arguments[2],o=\"\";if(!1!==n){var r=new Date;r.setTime(r.getTime()+24*n*60*60*1e3),o=\";expires=\"+r.toUTCString()}document.cookie=e+\"=\"+t+o+\";path=/\"},r.getCookie=function(e){for(var t=1<arguments.length&&void 0!==arguments[1]?arguments[1]:\"\",n=e+\"=\",o=document.cookie.split(\";\"),r=0;r<o.length;r++){for(var a=o[r];\" \"===a.charAt(0);)a=a.substring(1);if(0===a.indexOf(n))return a.substring(n.length,a.length)}return t}}function scaleString(e,t,n){return((\"number\"==typeof e?e:parseInt(e))/t).toFixed(n)}function formatUpdate(e){if(!1===e)return\"N/A\";var t=e/60,n=e/3600,o=n/24,r=e.toFixed(0)+\"s\";return 0===e.toFixed(0)?r=\"now\":7<o?r=\"inactive\":2<o?r=o.toFixed(1)+\" days\":2<n?r=n.toFixed(0)+\" hrs\":180<e&&(r=t.toFixed(0)+\" mins\"),r}function updateClass(e){if(!1===e)return\"\";var t=\"updateBad\";return(e=Math.abs(e))<25?t=\"updateGood\":e<60?t=\"updateSlow\":e<7200&&(t=\"updateSlower\"),t}!function(){var t=window.location.hostname,n=window.location.port,o=window.location.protocol;$(function(){var e=new OpenEvseWiFiViewModel(t,n,o);ko.applyBindings(e),e.start()})}();\n"
  "//# sourceMappingURL=home.js.map\n";
