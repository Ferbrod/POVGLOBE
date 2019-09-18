var Camara;
var BotonesEntrenar;
var knn;
var modelo;
var Texto;
var Clasificando = false;

let BrokerMQTT = 'broker.shiftr.io';
let PuertoMQTT = 80;
let ClienteIDMQTT = "ControlNeo";
let UsuarioMQTT = "HolaTodos";
let ContrasenaMQTT = "MundoPasivo";

client = new Paho.MQTT.Client(BrokerMQTT, PuertoMQTT, ClienteIDMQTT);

// set callback handlers
client.onConnectionLost = MQTTPerder;
client.onMessageArrived = MQTTMensaje;

client.connect({
  onSuccess: CuandoConectadoMQTT,
  userName: UsuarioMQTT,
  password: ContrasenaMQTT
});

function MQTTPerder(responseObject) {
  if (responseObject.errorCode !== 0) {
    console.log("MQTT Perdio coneccion Error:" + responseObject.errorMessage);
  }
}

function MQTTMensaje(message) {
  console.log("Mensaje recibido:" + message.payloadString);
}

function CuandoConectadoMQTT() {
  console.log("MQTT Conectado");
}



function setup() {
  createCanvas(320, 240);
  background(255, 0, 0);
  Camara = createCapture(VIDEO);
  Camara.size(320, 240);
  Camara.hide();

  modelo = ml5.featureExtractor('MobileNet', ModeloListo);
  knn = ml5.KNNClassifier();

  createP('Presiona Botones para entrenar');

  var BotonArcoiris = createButton("Arcoiris");
  BotonArcoiris.class("BotonEntrenar");

  var BotonRojo = createButton("Rojo");
  BotonRojo.class("BotonEntrenar");

  var BotonVerde = createButton("Verde");
  BotonVerde.class("BotonEntrenar");

  var BotonAzul = createButton("Azul");
  BotonAzul.class("BotonEntrenar");

  var BotonBlanco = createButton("Blanco");
  BotonBlanco.class("BotonEntrenar");

  Texto = createP("Modelo no Listo, esperando");

  BotonesEntrenar = selectAll(".BotonEntrenar");

  for (var B = 0; B < BotonesEntrenar.length; B++) {
    BotonesEntrenar[B].style("margin", "5px");
    BotonesEntrenar[B].style("padding", "6px");
    BotonesEntrenar[B].mousePressed(PresionandoBoton);
  }
}

function PresionandoBoton() {
  var NombreBoton = this.elt.innerHTML;
  console.log("Entrenando con " + NombreBoton);
  message = new Paho.MQTT.Message(NombreBoton);
     message.destinationName = "Control/rutinas";
     client.send(message);
  //EntrenarKnn(NombreBoton);
}

function EntrenarKnn(ObjetoEntrenar) {
  const Imagen = modelo.infer(Camara);
  knn.addExample(Imagen, ObjetoEntrenar);
}

function ModeloListo() {
  console.log("Modelo Listo");
  Texto.html("Modelo Listo");
}

function clasificar() {
  const Imagen = modelo.infer(Camara);
  knn.classify(Imagen, function(error, result) {
    if (error) {
      console.error();
    } else {
      Texto.html("Es un " + result.label);
      //clasificar();
    }
  })
}

function draw() {
  image(Camara, 0, 0, 320, 240);
  if (knn.getNumLabels() > 0 && !Clasificando) {
    //clasificar();
    setInterval(clasificar, 500);
    Clasificando = true;
  }
}
