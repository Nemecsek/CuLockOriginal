
String html1 = R""""(
    <!DOCTYPE html>
    <html>
    <head>
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <link rel="icon" href="data:,">
        <style>

        body {
            font-family: Arial, Helvetica, sans-serif;
            font-size: 12pt;
            font-weight: 700;
            background-color: aliceblue;
        }

        .small_button {
            width: 50px;
            height: 25px;
            border: none;
            padding: 3px;
            margin: 2px;
            text-align: center;
            text-decoration: none;
            display: inline-block;
            background-color: lightgray;
        }

        .big_button {
            width: 100px;
            height: 25px;
            border: none;
            padding: 3px;
            margin: 2px;
            text-align: center;
            text-decoration: none;
            display: inline-block;
            background-color: lightgray;
        }

        p {
            font-family: Arial, Helvetica, sans-serif;
            font-size: 10pt;
            font-weight: 500;
            color: dodgerblue;
        }

        .nice_input {
            width: 100px;
            height: 25px;
            border: none;
            padding: 3px;
            margin: 2px;
            display: inline-block;
            background-color: yellow;
            border: none;
        }

        </style>
    </head>
    <body>
        <center><h3>CuLock &omega;</h3></center>
)"""";

String html2 = R""""(
        <form>
            <button class="big_button" style="color:black" disabled>WiFi SSID</button>
            <input class="nice_background" type="text" id="wifis" name="wifis" value="" onkeydown="if (event.keyCode == 13) { this.form.submit(); }">
        </form>
        <form>
            <button class="big_button" style="color:black" disabled>WiFi Pwd</button>
            <input class="nice_background" type="text" id="wifip" name="wifip" value="" onkeydown="if (event.keyCode == 13) { this.form.submit(); }">
        </form>
)"""";

String html3 = R""""(
        <form>
            <button class="big_button" style="color:black" disabled>Time</button>
            <input class="nice_background" type="time" id="time" name="time" step=1 onchange="this.form.submit()">
        </form>

        <br>
        <center><form>
            <button class="small_button" name="language" id="language" value="0" type=submit">EN</button>
            <button class="small_button" name="language" id="language" value="1" type=submit">IT</button>
            <button class="small_button" name="language" id="language" value="2" type=submit">VN</button>
            <button class="small_button" name="language" id="language" value="3" type=submit">DE</button>
            <button class="small_button" name="language" id="language" value="4" type=submit">ES</button>
        </form>
        <br>
        <form>
            <button class="big_button" name="text_color" id="text_color" style="background:#fff;" value="111" type="submit">white</button>
            <button class="big_button" name="text_color" id="text_color" style="background:#ff8;" value="112" type="submit">lightyellow</button>
            <button class="big_button" name="text_color" id="text_color" style="background:#ff2;" value="114" type="submit">yellow</button>
            <button class="big_button" name="text_color" id="text_color" style="background:#f88;" value="122" type="submit">peach</button>
            <button class="big_button" name="text_color" id="text_color" style="background:#f82;" value="124" type="submit">orange</button>
            <button class="big_button" name="text_color" id="text_color" style="background:#f22;" value="144" type="submit">red</button>
            <button class="big_button" name="text_color" id="text_color" style="background:#f28;" value="142" type="submit">light red</button>
            <button class="big_button" name="text_color" id="text_color" style="background:#f2f;" value="141" type="submit">fuchsia</button>
            <button class="big_button" name="text_color" id="text_color" style="background:#f8f;" value="121" type="submit">pink</button>
            <button class="big_button" name="text_color" id="text_color" style="background:#82f;" value="241" type="submit">lila</button>
            <button class="big_button" name="text_color" id="text_color" style="background:#828;" value="242" type="submit">red-lila</button>
            <button class="big_button" name="text_color" id="text_color" style="background:#822;" value="244" type="submit">brown</button>
            <button class="big_button" name="text_color" id="text_color" style="background:#444;" value="444" type="submit">dark gray</button>
            <button class="big_button" name="text_color" id="text_color" style="background:#888;" value="222" type="submit">medium gray</button>
            <button class="big_button" name="text_color" id="text_color" style="background:#882;" value="224" type="submit">mustard</button>
            <button class="big_button" name="text_color" id="text_color" style="background:#288;" value="422" type="submit">sea green</button>
            <button class="big_button" name="text_color" id="text_color" style="background:#282;" value="424" type="submit">dark green</button>
            <button class="big_button" name="text_color" id="text_color" style="background:#2f2;" value="414" type="submit">green</button>
            <button class="big_button" name="text_color" id="text_color" style="background:#2f8;" value="412" type="submit">light green</button>
            <button class="big_button" name="text_color" id="text_color" style="background:#8ff;" value="211" type="submit">white sky</button>
            <button class="big_button" name="text_color" id="text_color" style="background:#2ff;" value="411" type="submit">sky blue</button>
            <button class="big_button" name="text_color" id="text_color" style="background:#28f;" value="421" type="submit">light blue</button>
            <button class="big_button" name="text_color" id="text_color" style="background:#22f;" value="441" type="submit">blue</button>
            <button class="big_button" name="text_color" id="text_color" style="background:#228;" value="442" type="submit">dark blue</button>
        </form>
        <br>
        <form>
            <button class="big_button" name="gray" id="gray" value="1" style="background:#CCC;" type="submit">Gray1</button>
            <button class="big_button" name="gray" id="gray" value="2" style="background:#AAA;" type="submit">Gray2</button>
            <button class="big_button" name="gray" id="gray" value="3" style="background:#888;" type="submit">Gray3</button>
        </form>
        <form>
            <button class="big_button" name="brightness" id="brightness" value="1" style="background:#CCC;" type="submit">Back1</button>
            <button class="big_button" name="brightness" id="brightness" value="2" style="background:#AAA; "type="submit">Back2</button>
            <button class="big_button" name="brightness" id="brightness" value="3" style="background:#888; "type="submit">Back3</button>
        </form>
        <form>
            <button class="big_button" name="rotate" id="rotate" value="1" type="submit">Rotate</button>
            <button class="big_button" name="debug"  id="debug"  value="1" type="submit">Debug</button>
        </form>
        </center>
)"""";
