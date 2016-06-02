from django.shortcuts import render
from django.http import HttpResponse
from sensor.models import Sensor
from lamp.models import Lamp
from datetime import datetime

# Create your views here.
import time 
from pytz import timezone as timeZone
def PushData(request):
	if request.method == "GET":
		print request
		idLampGet = request.GET['idlamp']
		soundGet= request.GET['sound']
		passiveInfraredGet= request.GET['passiveInfrared']
		lampGet = Lamp(id=idLampGet);
		vietnam = timeZone('Asia/Bangkok')
		timeGet = datetime.now(vietnam).strftime('%Y-%m-%d %H:%M:%S')
		saveData= Sensor(lamp=lampGet,sound=soundGet,passiveInfrared=passiveInfraredGet,time=timeGet)
		saveData.save()
	return HttpResponse("Done Upload")