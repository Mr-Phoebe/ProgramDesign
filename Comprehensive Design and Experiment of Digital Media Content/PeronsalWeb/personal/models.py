from __future__ import unicode_literals

from django.db import models
# Create your models here.

class UploadFile(models.Model):
    file_name = models.CharField(max_length=32, null=True)
    upload_time = models.DateTimeField(auto_now=True)




