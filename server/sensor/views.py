from django.shortcuts import render
from django.http import HttpResponse
from sensor.models import Sensor

# Create your views here.

def PushData(request):
	if request.method == "GET":
		print request
		idLampGet = request.GET['idlamp']
		soundGet= request.GET['sound']
		passiveInfraredGet= request.GET['passiveInfrared']
		saveData= Sensor(idLamp=idLampGet,sound=soundGet,passiveInfrared=passiveInfraredGet)
		saveData.save()
	return HttpResponse("Done Upload")