from django.shortcuts import render
from lcdRGB.models  import rgb
from django.http import HttpResponse
import urllib2, urllib, json
from rest_framework.renderers import JSONRenderer
# Create your views here.
class JSONResponse(HttpResponse):
    """
    An HttpResponse that renders its content into JSON.
    """
    def __init__(self, data, **kwargs):
        content = JSONRenderer().render(data)
        kwargs['content_type'] = 'application/json'
        super(JSONResponse, self).__init__(content, **kwargs)

def UpdateRGB(request):
	if request.method == "GET":
		print request
		idLampGet = request.GET['id']
		red= request.GET['red']
		green= request.GET['green']
		blue= request.GET['blue']
		rgbO = rgb.objects.get(id=idLampGet)
		rgbO.red = red;
		rgbO.green = green;
		rgbO.blue = blue; 
		rgbO.save()
	return HttpResponse("Done Upload")

def GetRGB(request):
	if request.method =="GET":
		idLampGet = request.GET['id']
		rgbO =rgb.objects.get(id=idLampGet)
		result = {}
		result['red']=rgbO.red;
		result['green']=rgbO.green;
		result['blue']=rgbO.blue;
		resultAPI =JSONResponse(result)
		return resultAPI