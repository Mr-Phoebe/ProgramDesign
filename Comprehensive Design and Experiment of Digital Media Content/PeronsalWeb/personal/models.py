from __future__ import unicode_literals

from django.db import models
from django import forms
# Create your models here.

class UploadFile(models.Model):
    file_name = models.CharField(max_length=32, null=True)
    upload_time = models.DateTimeField(auto_now=True)


class UploadFileForm(forms.Form):
    title = forms.CharField(max_length=64)
    fileType = forms.CharField(max_length=32)
    theFile = forms.FileField()



