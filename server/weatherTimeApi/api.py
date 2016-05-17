from rest_framework.response import Response
from datetime import datetime
from pytz import timezone
from rest_framework import views
import requests
import urllib

class GetDateTime(views.APIView):

  def get(self, request, format=None):
    fdate = "%a,%b %d,%Y"
    fhours = "%H"
    fminutes = "%M"
    fseconds = "%S"
    now_utc = datetime.now(timezone('Asia/Bangkok'))

    date = now_utc.strftime(fdate)
    hours = now_utc.strftime(fhours)
    minutes = now_utc.strftime(fminutes)
    seconds = now_utc.strftime(fseconds)

    return Response({"date":date,"hours":hours,"minutes":minutes,"seconds":seconds},200);

class GetWeather(views.APIView):

  def get(self,request,format=None):
    city = "Da Nang"
    baseurl = "https://query.yahooapis.com/v1/public/yql?"
    yql_query = "select * from weather.forecast where woeid in (select woeid from geo.places(1) where text='"+city+"') and u='c'"
    yql_url = baseurl + urllib.urlencode({'q':yql_query}) + "&format=json"

    data = requests.get(yql_url).json();
    result = data["query"]['results']['channel']['item']['condition']
    return Response(result,200);

class GetForecast(views.APIView):
  def get(self,request,format=None):
    city = "Da Nang"
    baseurl = "https://query.yahooapis.com/v1/public/yql?"
    yql_query = "select * from weather.forecast where woeid in (select woeid from geo.places(1) where text='"+city+"') and u='c'"
    yql_url = baseurl + urllib.urlencode({'q':yql_query}) + "&format=json"

    data = requests.get(yql_url).json();
    result = data["query"]['results']['channel']['item']['forecast'][0:3]
    return Response(result,200);
    