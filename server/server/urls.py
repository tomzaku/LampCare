"""server URL Configuration

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/1.9/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  url(r'^$', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  url(r'^$', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.conf.urls import url, include
    2. Add a URL to urlpatterns:  url(r'^blog/', include('blog.urls'))
"""
from django.conf.urls import url,include
from django.contrib import admin
from django.contrib.auth.models import User
from sensor import views
from django.http import HttpResponse
from rest_framework import routers, serializers, viewsets
from sensor.serializer import SensorViewSet
import weatherTimeApi.urls as WTurls

# Routers provide an easy way of automatically determining the URL conf.
router = routers.DefaultRouter()
router.register(r'sensor', SensorViewSet)


class UserSerializer(serializers.HyperlinkedModelSerializer):
    class Meta:
        model = User
        fields = ('url', 'username', 'email', 'is_staff')

# ViewSets define the view behavior.
class UserViewSet(viewsets.ModelViewSet):
    queryset = User.objects.all()
    serializer_class = UserSerializer

    
router.register(r'users', UserViewSet)

# router = routers.DefaultRouter()
# router.register(r'sensorSound',soundAnalogViewSet)





def main(reponse):
	return HttpResponse("MAIN")
urlpatterns = [
    url(r'^admin/', admin.site.urls),
    url(r'^api-post/',views.PushData),
    url(r'^$',main),
    url(r'^api', include(router.urls)),
    # url(r'^api-auth/', include('rest_framework.urls', namespace='rest_framework')),
    url(r'api-time/',include(WTurls))
]
