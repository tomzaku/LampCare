from django.conf.urls import include, url
import api as weather_api

urlpatterns = [
    url(r'datetime/$', weather_api.GetDateTime.as_view(), name='datetime'),
    url(r'weather/$', weather_api.GetWeather.as_view(), name='datetime'),
    url(r'forcecast/$', weather_api.GetForecast.as_view(), name='datetime'),
]