from __future__ import unicode_literals

from django.db import models

# Create your models here.

class rgb(models.Model):
	id = models.IntegerField(primary_key=True)
	red = models.IntegerField(default =0)
	green = models.IntegerField(default =0)
	blue = models.IntegerField(default =0)
	def __str__(self):
		return unicode(self.id)
