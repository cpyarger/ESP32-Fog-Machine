
const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<style>
.card{
    max-width: 400px;
     min-height: 250px;
     background: #02b875;
     padding: 30px;
     box-sizing: border-box;
     color: #FFF;
     margin:20px;
     box-shadow: 0px 2px 18px -4px rgba(0,0,0,0.75);
}
     .myButton {
 -moz-box-shadow:inset 0px 0px 3px 0px #91b8b3;
  -webkit-box-shadow:inset 0px 0px 3px 0px #91b8b3;
  box-shadow:inset 0px 0px 3px 0px #91b8b3;
  background:-webkit-gradient(linear, left top, left bottom, color-stop(0.05, #768d87), color-stop(1, #6c7c7c));
  background:-moz-linear-gradient(top, #768d87 5%, #6c7c7c 100%);
  background:-webkit-linear-gradient(top, #768d87 5%, #6c7c7c 100%);
  background:-o-linear-gradient(top, #768d87 5%, #6c7c7c 100%);
  background:-ms-linear-gradient(top, #768d87 5%, #6c7c7c 100%);
  background:linear-gradient(to bottom, #768d87 5%, #6c7c7c 100%);
  filter:progid:DXImageTransform.Microsoft.gradient(startColorstr='#768d87', endColorstr='#6c7c7c',GradientType=0);
  background-color:#768d87;
  -moz-border-radius:7px;
  -webkit-border-radius:7px;
  border-radius:7px;
  border:2px solid #566963;
  display:inline-block;
  cursor:pointer;
  color:#ffffff;
  font-family:Arial;
  font-size:20px;
  font-weight:bold;
  padding:11px 23px;
  text-decoration:none;
  text-shadow:1px 2px 2px #2b665e;
}
.myButton:hover {
  background:-webkit-gradient(linear, left top, left bottom, color-stop(0.05, #6c7c7c), color-stop(1, #768d87));
  background:-moz-linear-gradient(top, #6c7c7c 5%, #768d87 100%);
  background:-webkit-linear-gradient(top, #6c7c7c 5%, #768d87 100%);
  background:-o-linear-gradient(top, #6c7c7c 5%, #768d87 100%);
  background:-ms-linear-gradient(top, #6c7c7c 5%, #768d87 100%);
  background:linear-gradient(to bottom, #6c7c7c 5%, #768d87 100%);
  filter:progid:DXImageTransform.Microsoft.gradient(startColorstr='#6c7c7c', endColorstr='#768d87',GradientType=0);
  background-color:#6c7c7c;
}
.myButton:active {
  position:relative;
  top:1px;
}
</style>
<body>
<center>
<h1> Fog Machine Info </h1>
<div class="header">
<a href="/"><button class="mybutton">Main</button></a><a href="/setup"><button class="mybutton">Setup</button></a>
</div>
<div class="card">
  <h4>Fog Machine Temp:  <span id="ADCValue">--</span></h4><br>
  <h1><div class="slidecontainer">
  dur: <input type="range" min="1" max="255" value="50" class="slider" id="DURValue"><span id="dur">--</span>
</div></h1><br>
  <h1><div class="slidecontainer">
  Delay: <input type="range" min="1" max="255" value="50" class="slider" id="DELValue"><span id="del">--</span>
</div></h1><br>
  <br>
</div>


</center>
<script>

setInterval(function() {
  // Call a function repetatively with 2 Second interval
  getData();
  getDur();
  getDel();
}, 2000); //2000mSeconds update rate

function getData() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("ADCValue").innerHTML =
      this.responseText;
      
    }
  };
  xhttp.open("GET", "readADC", true);
  xhttp.send();
}   
function getDur() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      x=this.responseText;
      document.getElementById("DURValue").value = x;
      document.getElementById("dur").innerHTML = x;
    }
  };
  xhttp.open("GET", "readDUR", true);
  xhttp.send();
}  
function getDel() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      x=this.responseText;
      document.getElementById("DELValue").value = x;
      document.getElementById("del").innerHTML = x;
    }
  };
  xhttp.open("GET", "readDEL", true);
  xhttp.send();
}  
</script>
</body>
</html>
)=====";
