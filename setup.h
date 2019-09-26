/* on this page includes
    WIFI Setup
    ArtNet Setup

*/
const char SETUP_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
 <script>
 
        function getADR() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("ADR").value =
      this.responseText;
    }
  };
  xhttp.open("GET", "readADR", true);
  xhttp.send();
} 
function getSS() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("SS").value =
      this.responseText;
    }
  };
  xhttp.open("GET", "readSS", true);
  xhttp.send();
} 
function getPW() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("PW").value =
      this.responseText;
    }
  };
  xhttp.open("GET", "readPW", true);
  xhttp.send();
} 
function getUNI() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("UNI").value =
      this.responseText;
    }
  };
  xhttp.open("GET", "readUNI", true);
  xhttp.send();
} 

function myFunction() {
  // Call a function repetatively with 2 Second interval
  getSS();
   getADR();
    getUNI();
     getPW();
     
};
</script>
    
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
</head>
<body onload="myFunction()">
<center>
<h1> Fog Machine Setup </h1>
<div class="header">
<a href="/"><button class="mybutton">Main</button></a><a href="/setup"><button class="mybutton">Setup</button></a><button id="save_button" class="mybutton">Save</button>

</div>
<div class="card">
  <h4>Wifi Setup</h4><br>
  Default Connection Type (internal AP or external AP) <br>
  
   <br>
  SSID <input id="SS"><br>
  Password<input id="PW"><br>
</div>

<div class="card">
  <h4>ArtNet Setup</h4><br>
  Universe: <input id="UNI"><br>
  <br>Starting Address: <input id="ADR"></a>
  
</div>

<br >
 
</center>
  <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.3/jquery.min.js"></script>


<script>
      var ss;
      var pw;
      var uni;
      var adr;
      $('#save_button').click(function(e){
        e.preventDefault();
        ss = $('#SS').val();
        pw = $('#PW').val();
        uni = $('#UNI').val();
        adr = $('#ADR').val();         
        $.get('/save?ss=' + ss + '&pw=' + pw + '&uni=' + uni+ '&adr=' + adr, function(data){
          console.log(data);
        });
      }); 

    </script>
</body>
</html>
)=====";
