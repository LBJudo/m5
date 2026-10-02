#include <M5Unified.h>
#include <WiFi.h>
#include <WebServer.h>

// Configuration Wi-Fi
const char* ssid = "CollegeDromeWifi";
const char* password = "Wifi@Drome26";

WebServer server(80);

// Code HTML / CSS / JS du site "NE PAS CLIQUER"
const char HTML_CONTENT[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="fr">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1, viewport-fit=cover">
<title>NE PAS CLIQUER</title>
<link href="https://fonts.googleapis.com/css2?family=Rubik+Mono+One&display=swap" rel="stylesheet">
<style>
:root{--bg:#ffe600;--ink:#16001f;--hot:#ff1f8e;box-sizing:border-box;padding-top:env(safe-area-inset-top,0px);padding-bottom:env(safe-area-inset-bottom,0px)}
@media (prefers-color-scheme:dark){:root:not([data-theme="light"]){--bg:#ffe600;--ink:#16001f}}
:root[data-theme="dark"]{--bg:#ffe600;--ink:#16001f}
*{box-sizing:border-box}
html,body{height:100%;margin:0}
body{background:var(--bg);color:var(--ink);font-family:"Rubik Mono One",Impact,"Arial Black",sans-serif;overflow:hidden;position:relative;cursor:none;transition:background .4s,filter .3s}
body.inv{filter:invert(1) hue-rotate(160deg)}
body.shake{animation:sh .12s infinite}
body.comic{background:#ff9ad5}
body.comic *{font-family:"Comic Sans MS","Comic Neue",cursive!important}
@keyframes sh{0%{transform:translate(4px,-3px) rotate(.4deg)}50%{transform:translate(-5px,4px) rotate(-.5deg)}100%{transform:translate(3px,5px) rotate(.3deg)}}
#stage{position:absolute;inset:0;transition:transform 1.2s}
h1{position:absolute;left:0;right:0;top:12%;margin:0;text-align:center;font-size:clamp(34px,10vw,120px);line-height:1;font-weight:400;padding:0 12px}
h1 span{display:inline-block;transition:transform 1.4s cubic-bezier(.5,0,1,.6)}
#log{position:absolute;left:0;right:0;top:46%;text-align:center;font-size:clamp(12px,2.6vw,20px);padding:0 16px;min-height:3em}
#btn{position:absolute;left:50%;top:68%;transform:translate(-50%,-50%);font:inherit;font-size:clamp(18px,4vw,34px);padding:.7em 1.1em;border:5px solid var(--ink);background:var(--hot);color:#fff;cursor:none;box-shadow:8px 8px 0 var(--ink);transition:left .25s,top .25s,font-size .5s}
#btn:focus-visible{outline:4px dashed var(--ink);outline-offset:6px}
#btn:active{box-shadow:2px 2px 0 var(--ink)}
#count{position:absolute;right:14px;bottom:10px;font-size:12px}
.cur{position:fixed;left:0;top:0;font-size:34px;pointer-events:none;z-index:99;transform:translate(-50%,-50%)}
#kill,#bsod{position:fixed;inset:0;z-index:50;display:none;padding:7vw;font-family:ui-monospace,Menlo,Consolas,monospace;font-size:clamp(13px,3vw,22px)}
#kill{background:#000;color:#39ff14}
#bsod{background:#0000aa;color:#fff;z-index:55}
pre{white-space:pre-wrap;margin:0}
#bar{height:26px;border:2px solid #39ff14;margin-top:20px}
#bar i{display:block;height:100%;width:0;background:#39ff14}
#eyes{position:fixed;inset:0;z-index:60;display:none;background:#16001f}
.eye{position:absolute;width:74px;height:74px;border-radius:50%;background:#fff;overflow:hidden}
.eye b{position:absolute;width:30px;height:30px;border-radius:50%;background:#16001f;left:22px;top:22px}
.eye b::after{content:"";position:absolute;width:9px;height:9px;border-radius:50%;background:#fff;left:6px;top:5px}
#msg{position:fixed;left:0;right:0;bottom:8%;text-align:center;color:#fff;z-index:70;font-size:clamp(16px,4vw,36px);display:none;padding:0 16px}
#again{position:fixed;left:50%;bottom:2%;transform:translateX(-50%);z-index:80;display:none;font:inherit;font-size:13px;padding:.6em 1em;background:#fff;border:3px solid #fff;cursor:none}
#toast{position:fixed;left:50%;top:12px;transform:translateX(-50%);background:#16001f;color:#fff;border:3px solid var(--hot);padding:.8em 1.1em;z-index:40;display:none;font-size:clamp(12px,2.8vw,18px);max-width:92vw;text-align:center}
#cookie{position:fixed;left:0;right:0;bottom:0;background:#fff;color:#000;border-top:5px solid #000;padding:14px;z-index:41;display:none;font:14px sans-serif;text-align:center}
#cookie button{font:inherit;margin:6px;padding:8px 14px;cursor:none}
.pop{position:fixed;z-index:42;background:#c0c0c0;color:#000;border:3px outset #fff;padding:0;width:min(230px,70vw);font:13px sans-serif}
.pop h4{margin:0;background:#000080;color:#fff;padding:3px 6px;display:flex;justify-content:space-between}
.pop p{margin:10px}
.pop button{cursor:none}
.rain{position:fixed;top:-60px;font-size:36px;z-index:30;pointer-events:none;animation:rn linear forwards}
@keyframes rn{to{transform:translateY(115vh) rotate(360deg)}}
#crack{position:fixed;inset:0;z-index:35;pointer-events:none;width:100%;height:100%;display:none}
#modal{position:fixed;inset:0;z-index:90;background:rgba(0,0,0,.7);display:none;align-items:center;justify-content:center}
#modal div{background:#fff;color:#000;padding:22px;font:16px sans-serif;max-width:84vw;text-align:center;border:3px solid #000}
#modal button{margin-top:14px;font:inherit;padding:8px 22px;cursor:none}
@media (prefers-reduced-motion:reduce){body.shake{animation:none}}
</style>
</head>
<body>
<div id="stage">
<h1 id="t">NE PAS CLIQUER</h1>
<div id="log">Vraiment. Ça ne sert à rien.</div>
<button id="btn" type="button">CLIQUER</button>
<div id="count">clics : 0</div>
</div>
<div class="cur" id="cur">🖱️</div>
<div id="toast"></div>
<div id="cookie">🍪 Ce site utilise des cookies pour te regarder cliquer.<br><button>Accepter</button><button>Accepter quand même</button></div>
<div id="kill"><pre id="kt"></pre><div id="bar"><i></i></div></div>
<div id="bsod"><pre>:(

Ton écran a rencontré un problème et doit redémarrer son âme.

Code d'arrêt : TROP_DE_CLICS
Redémarrage dans quelques secondes...</pre></div>
<svg id="crack" xmlns="http://www.w3.org/2000/svg"></svg>
<div id="modal"><div id="mb"></div></div>
<div id="eyes"></div>
<div id="msg"></div>
<button id="again" type="button">recommencer (si tu oses)</button>
<script>
var $=function(s){return document.querySelector(s)},B=document.body,btn=$("#btn"),log=$("#log"),cur=$("#cur"),t=$("#t"),st=$("#stage");
var n=0,mx=innerWidth/2,my=innerHeight/2,cx=mx,cy=my,dead=false,eyes=[],trail=[],hist=[],tease=false;
function say(s){log.textContent=s}
function toast(s,ms){var e=$("#toast");e.textContent=s;e.style.display="block";setTimeout(function(){e.style.display="none"},ms||3500)}
function over(id,ms){var e=$(id);e.style.display="block";setTimeout(function(){e.style.display="none"},ms)}
function R(a,b){return a+Math.random()*(b-a)}
function build(s){t.innerHTML=s.split("").map(function(c){return c==" "?" ":"<span>"+c+"</span>"}).join("")}
build(t.textContent);
addEventListener("pointermove",function(e){mx=e.clientX;my=e.clientY});
(function loop(){var k=dead?.04:.25;cx+=(mx-cx)*k;cy+=(my-cy)*k;
 if(dead){cx+=(Math.random()-.5)*6;cy+=(Math.random()-.5)*6}
 cur.style.left=cx+"px";cur.style.top=cy+"px";
 hist.unshift([cx,cy]);if(hist.length>90)hist.pop();
 trail.forEach(function(el,i){var h=hist[(i+1)*4];if(h){el.style.left=h[0]+"px";el.style.top=h[1]+"px"}});
 eyes.forEach(function(e){var r=e.el.getBoundingClientRect(),a=Math.atan2(my-(r.top+r.height/2),mx-(r.left+r.width/2)),k=r.width/74;
  e.p.style.left=22+Math.cos(a)*18+"px";e.p.style.top=22+Math.sin(a)*18+"px"});
 requestAnimationFrame(loop)})();

function fall(){document.querySelectorAll("#t span").forEach(function(s,i){
 setTimeout(function(){s.style.transform="translateY("+(innerHeight*.7+R(0,80))+"px) rotate("+R(-80,80)+"deg)"},i*90)})}
function runaway(){btn.style.left=R(15,85)+"%";btn.style.top=R(55,85)+"%"}
btn.addEventListener("mouseenter",function(){if(tease)runaway()});
function wipe(){
 var k=$("#kill"),kt=$("#kt"),b=$("#bar i");k.style.display="block";b.style.width="0";b.style.background="#39ff14";
 var lines=["Connexion au disque dur...","Trouvé : tes photos de vacances","Trouvé : 14 onglets que tu comptais lire","Trouvé : ce mot de passe que tu réutilises partout","Suppression en cours..."],i=0,p=0;kt.textContent="";
 var li=setInterval(function(){if(i<lines.length){kt.textContent+="> "+lines[i++]+"\n"}else clearInterval(li)},600);
 var pi=setInterval(function(){p+=R(0,5);if(p>=87){p=87;clearInterval(pi);
  setTimeout(function(){kt.textContent+="\n> ERREUR : impossible de supprimer ta dignité.\n> Elle était déjà partie.";b.style.width="100%";b.style.background="#ff1f8e";
   setTimeout(function(){k.style.display="none"},2400)},800)}
  b.style.width=p+"%"},110);
}
function pops(){var msgs=["Tu as gagné 1 000 000 € !","Ton PC a 47 virus. Un seul est le tien.","Une MILF célibataire habite dans ton salon","Clique ici pour fermer cette fenêtre","Télécharge plus de RAM"];
 for(var i=0;i<6;i++)(function(i){setTimeout(function(){var p=document.createElement("div");p.className="pop";
  p.style.left=R(2,55)+"%";p.style.top=R(8,70)+"%";p.innerHTML="<h4>Alerte !<button>x</button></h4><p>"+msgs[i%5]+"</p>";
  p.querySelector("button").onclick=function(){p.remove()};document.body.appendChild(p);
  setTimeout(function(){p.remove()},7000)},i*350)})(i)}
function rain(e){for(var i=0;i<45;i++){var d=document.createElement("div");d.className="rain";d.textContent=e;
 d.style.left=R(0,98)+"%";d.style.animationDuration=R(2,5)+"s";d.style.animationDelay=R(0,2)+"s";document.body.appendChild(d);
 (function(d){setTimeout(function(){d.remove()},8000)})(d)}}
function crack(){var s=$("#crack"),w=innerWidth,h=innerHeight,x=R(.3,.7)*w,y=R(.3,.7)*h,h2="";s.style.display="block";
 for(var i=0;i<9;i++){var a=i*Math.PI/4.5+R(-.2,.2),px=x,py=y,d="M"+px+" "+py;
  for(var j=0;j<6;j++){a+=R(-.5,.5);px+=Math.cos(a)*R(30,110);py+=Math.sin(a)*R(30,110);d+="L"+px+" "+py}
  h2+='<path d="'+d+'" stroke="#fff" stroke-width="2" fill="none" opacity=".85"/><path d="'+d+'" stroke="#000" stroke-width="1" fill="none" transform="translate(2 2)"/>'}
 s.innerHTML=h2}
function modal(s,ok){$("#mb").innerHTML=s+"<br><button>"+ok+"</button>";$("#modal").style.display="flex";
 $("#mb button").onclick=function(){$("#modal").style.display="none"}}
function finale(){
 var e=$("#eyes");e.style.display="block";
 for(var i=0;i<70;i++){var d=document.createElement("div");d.className="eye";d.style.left=R(0,100)+"%";d.style.top=R(0,100)+"%";
  var s=R(.6,2.2);d.style.transform="translate(-50%,-50%) scale("+s+")";d.innerHTML="<b></b>";e.appendChild(d);eyes.push({el:d,p:d.firstChild})}
 cur.textContent="💀";dead=true;
 var m=$("#msg");m.style.display="block";m.textContent="ILS T'ONT TOUJOURS REGARDÉ.";
 setTimeout(function(){m.textContent="Merci d'avoir perdu ton temps. C'était le but.";$("#again").style.display="block"},4200);
}
var stages=[
 function(){say("Bravo. Tu viens de cliquer sur un bouton. Quel exploit.");runaway()},
 function(){say("Tu aurais dû lire le titre.");fall()},
 function(){say("Ton curseur a un petit retard. C'est normal. Ou pas.");cx-=200;mx=cx;cur.textContent="👁️"},
 function(){B.classList.add("inv");say("Les couleurs ont changé. Personne ne sait pourquoi.");runaway()},
 function(){B.classList.add("shake");say("Ne panique pas. Surtout ne panique pas.");setTimeout(function(){B.classList.remove("shake");B.classList.remove("inv")},2000)},
 function(){wipe()},
 function(){say("Le bouton a rétréci. Il a honte.");btn.style.fontSize="7px";btn.style.padding="4px 6px";btn.style.borderWidth="2px";btn.style.boxShadow="2px 2px 0 #16001f"},
 function(){say("Maintenant il a pris confiance.");btn.style.fontSize="min(16vw,110px)";btn.style.padding=".4em .6em";btn.style.borderWidth="5px";btn.style.boxShadow="8px 8px 0 #16001f";btn.style.top="75%"},
 function(){say("Tout est à l'envers. Comme ta journée.");btn.style.fontSize="";btn.style.padding="";btn.style.top="68%";st.style.transform="rotate(180deg)"},
 function(){st.style.transform="";say("Retour à la normale. Presque.");toast("🔋 Batterie à 1 %. Ton cœur aussi ?",3500)},
 function(){say("On respecte ta vie privée. Un peu.");$("#cookie").style.display="block";$("#cookie").querySelectorAll("button").forEach(function(b){b.onclick=function(){$("#cookie").style.display="none"}});setTimeout(function(){$("#cookie").style.display="none"},6000)},
 function(){say("Il pleut du fromage. Pas de questions.");rain("🧀")},
 function(){say("Ferme-les tous. Bonne chance.");pops()},
 function(){say("Une mise à jour est nécessaire.");over("#bsod",3800)},
 function(){say("Tu as maintenant 14 curseurs. Lequel est le vrai ?");for(var i=0;i<14;i++){var d=document.createElement("div");d.className="cur";d.style.opacity=1-i/16;d.textContent="🖱️";document.body.appendChild(d);trail.push(d)}},
 function(){build("GAGA GOUGOU");say("Tu es tombé sur la tête ? Moi oui.");btn.textContent="BIBERON"},
 function(){say("Ta caméra vient de s'allumer.");toast("🔴 CAMÉRA ACTIVÉE — non, c'est faux. Mais tu as vérifié.",4200)},
 function(){B.classList.add("comic");say("Voilà. C'est devenu officiel : cette page est un crime de goût.");btn.textContent="PLUS FORT"},
 function(){st.style.transform="scaleX(-1)";say("!ꞁƎ ƎƧꓷƎNQ ƎᴚUOᴎ ᴎƎ ƎᴚUꓕꓕO ƎƎ ƎꞁƎƎ ᴎOꓕ — ça va ?")},
 function(){st.style.transform="";crack();say("L'écran est fissuré. Tu devras payer la réparation.")},
 function(){tease=true;btn.textContent="ATTRAPE-MOI";say("Je compte tes clics : "+n+". Je les garde. Tous.")},
 function(){tease=false;modal("Cette page a quitté Internet.<br>Elle a besoin de s'éloigner un peu.","Je comprends");say("Ça se termine bientôt. Probablement.")},
 function(){say("Dernier clic. Sérieusement cette fois.");rain("👁️")},
 function(){finale()}
];
btn.addEventListener("click",function(){if(n>=stages.length)return;stages[n]();n++;$("#count").textContent="clics : "+n+"/"+stages.length});
$("#again").addEventListener("click",function(){location.reload()});
</script>
</body>
</html>
)rawliteral";

void setup() {
    Serial.begin(115200);

    // Initialisation écran M5StickC S3
    auto cfg = M5.config();
    M5.begin(cfg);
    M5.Lcd.setRotation(1);
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setTextSize(1);

    M5.Lcd.setCursor(5, 5);
    M5.Lcd.println("Connexion WiFi...");

    // Connexion au réseau du collège
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        M5.Lcd.print(".");
        Serial.print(".");
    }

    Serial.println("\nWiFi Connecte !");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());

    // Affichage sur l'écran
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(5, 5);
    M5.Lcd.setTextColor(GREEN);
    M5.Lcd.println("WiFi Connecte !");
    
    M5.Lcd.setTextColor(YELLOW);
    M5.Lcd.setCursor(5, 25);
    M5.Lcd.print("IP: ");
    M5.Lcd.println(WiFi.localIP());

    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setCursor(5, 50);
    M5.Lcd.println("Tunnel Cloudflare :");

    // Envoi de la page Web au client HTTP
    server.on("/", []() {
        server.send(200, "text/html", HTML_CONTENT);
    });
    
    server.begin();
    M5.Lcd.setTextColor(CYAN);
    M5.Lcd.setCursor(5, 65);
    M5.Lcd.println("Serveur HTTP Pret");
}

void loop() {
    M5.update();
    server.handleClient();
}
