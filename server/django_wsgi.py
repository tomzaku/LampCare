import os
os.environ['DJANGO_SETTINGS_MODULE']='mysite.settings'
import django.core.handlers.wsgi

application = diango.core.handlers.wsgi.WSGIHandler()