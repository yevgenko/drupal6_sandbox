// http://www.einfach-fuer-alle.de/artikel/fontsize/
function Efa_Fontsize() {
  var settings = Drupal.settings.fontsize;
  this.w3c = (document.getElementById);
  this.ms = (document.all);
  this.userAgent = navigator.userAgent.toLowerCase();
  this.isOldOp = ((this.userAgent.indexOf('opera') != -1)&&(parseFloat(this.userAgent.substr(this.userAgent.indexOf('opera')+5)) <= 7));
  if ((this.w3c || this.ms) && !this.isOldOp && !this.isMacIE) {
    this.name = "efa_fontSize";
    this.cookieName = settings.cookieName;
    this.cookieExpires = settings.cookieExpires;
    this.cookiePath = settings.cookiePath;
    this.cookieDomain = settings.cookieDomain;
    this.min = settings.min;
    this.max = settings.max;
    this.def = settings.def;
    this.increment = settings.increment;
    this.defPx = Math.round(16*(settings.def/100));
    this.base = 1;
    this.pref = this.getPref();
    this.testHTML = '<div id="efaTest" style="position:absolute;visibility:hidden;line-height:1em;">&nbsp;</div>';
    this.biggerLink = this.getLinkHtml(1,settings.bigger);
    this.resetLink = this.getLinkHtml(0,settings.reset);
    this.smallerLink = this.getLinkHtml(-1,settings.smaller);
  } else {
    this.biggerLink = '';
    this.resetLink = '';
    this.smallerLink = '';
    this.efaInit = new Function('return true;');
  }
  this.allLinks = this.biggerLink + this.resetLink + this.smallerLink;
}
Efa_Fontsize.prototype.efaInit = function() {
  document.writeln(this.testHTML);
  this.body = (this.w3c)?document.getElementsByTagName('body')[0].style:document.all.tags('body')[0].style;
  this.efaTest = (this.w3c)?document.getElementById('efaTest'):document.all['efaTest'];
  var h = (this.efaTest.clientHeight)?parseInt(this.efaTest.clientHeight):(this.efaTest.offsetHeight)?parseInt(this.efaTest.offsetHeight):999;
  if (h < this.defPx) this.base = this.defPx/h;
  this.body.fontSize = Math.round(this.pref*this.base) + '%';
}
Efa_Fontsize.prototype.getLinkHtml = function(direction,properties) {
  var html = properties[0] + '<a href="#" onclick="efa_fontSize.setSize(' + direction + '); return false;"';
  html += (properties[2])?'title="' + properties[2] + '"':'';
  html += (properties[3])?'class="' + properties[3] + '"':'';
  html += (properties[4])?'id="' + properties[4] + '"':'';
  html += (properties[5])?'name="' + properties[5] + '"':'';
  html += (properties[6])?'accesskey="' + properties[6] + '"':'';
  html += (properties[7])?'onmouseover="' + properties[7] + '"':'';
  html += (properties[8])?'onmouseout="' + properties[8] + '"':'';
  html += (properties[9])?'onfocus="' + properties[9] + '"':'';
  return html += '>'+ properties[1] + '<' + '/a>' + properties[10];
}
Efa_Fontsize.prototype.getPref = function() {
  var pref = this.getCookie(this.cookieName);
  if (pref) return parseInt(pref);
  else return this.def;
}
Efa_Fontsize.prototype.setSize = function(direction) {
  this.pref = (direction)?(this.pref+(direction*this.increment)<=this.max)?(this.pref+(direction*this.increment)>=this.min)?this.pref+(direction*this.increment):this.min:this.max:this.def;
  this.setCookie(this.cookieName,this.pref);
  this.body.fontSize = Math.round(this.pref*this.base) + '%';
}
Efa_Fontsize.prototype.getCookie = function(cookieName) {
  var cookie = $.cookie(cookieName);
  return (cookie)?cookie:false;
}
Efa_Fontsize.prototype.setCookie = function(cookieName,cookieValue) {
  $.cookie(cookieName, cookieValue, {expires: this.cookieExpires, path: this.cookiePath, domain: this.cookieDomain});
}
