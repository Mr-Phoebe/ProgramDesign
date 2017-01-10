from django import forms

class UploadFileForm(forms.Form):
    title = forms.CharField(max_length=64)
    fileType = forms.CharField(max_length=32)
    theFile = forms.FileField()
    description = forms.CharField(max_length=80)