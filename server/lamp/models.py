from __future__ import unicode_literals

from django.db import models

# Create your models here.


class ModelLamp(models.Model):
	modelhash = models.CharField(max_length=30,blank=False)
	name = models.CharField(max_length=30,blank=False)
	def __str__(self):
		return unicode(self.name)

class Lamp(models.Model):
	name = models.CharField(max_length=30)
	modelLamp = models.ForeignKey(ModelLamp)
	def __str__(self):
		return unicode(self.name)
	