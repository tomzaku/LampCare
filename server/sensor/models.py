from __future__ import unicode_literals
from datetime import datetime
from django.db import models
from lamp.models import Lamp
# Create your models here.
class Sensor(models.Model):
	sound= models.IntegerField()
	passiveInfrared = models.IntegerField()
	time = models.DateTimeField(default=datetime.now, blank=False)
	lamp = models.ForeignKey(Lamp)
	def __str__(self):
		return unicode(self.sound)
