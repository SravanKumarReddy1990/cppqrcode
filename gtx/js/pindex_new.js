

var gridlayer=new ol.layer.Vector({
      title: 'TN PARLIAMENT',
      source: new ol.source.Vector({
         format: new ol.format.GeoJSON(),
         url: 'tnparliament.geojson'
      })
  });

var map = new ol.Map({
    target: 'map',
    layers: [
    new ol.layer.Tile({
      source: new ol.source.OSM()
    })
    ],
    view: new ol.View({
        center: ol.proj.transform([78.38745117187499,11.86466302072273], 'EPSG:4326', 'EPSG:3857'),
        zoom: 10
    })
});

map.on('click', function(evt) {
var lonlat = ol.proj.transform(evt.coordinate, 'EPSG:3857', 'EPSG:4326');
  var lon = lonlat[0];
  var lat = lonlat[1];

		
});

function checData(){
 //var point= new ol.geom.Point(ol.proj.transform(, 'EPSG:4326', 'EPSG:3857'))
//var input=layerWFS.getSource().getFeaturesAtCoordinate(point);

var coord = ol.proj.fromLonLat([77.519105,10.248160]);
var features=tamilWFS.getSource().getFeatures();	
features.forEach(function(feature){ 
var polygon_extent=feature.getGeometry().getExtent();
var att = feature.getProperties();
  var contains = ol.extent.containsCoordinate(polygon_extent, coord);
  console.info(contains+" , "+att.ac_name);
if(contains==true){
console.log(feature.getGeometry());
}

});
}
