#encoding: utf-8

import os

from django.shortcuts import render
from django.http import JsonResponse, HttpResponseRedirect
from django.views.decorators.csrf import csrf_exempt

from models import UploadFile
# Create your views here.

def index(request):
    count = UploadFile.objects.count()
    data = UploadFile.objects.all()
    resp = []
    for r in data:
        res = {}
        res['fileName'] = r.file_name
        res['uploadTime'] = str(r.upload_time)
        res['uploadPos'] = str(r.file_name)
        resp.append(res)
    return render(request, 'index.html', {'count': count, 'data': resp})

@csrf_exempt
def upload(request):
    if request.method == 'POST':
        try:
            upload_file = request.FILES['file']
            f = UploadFile()
            filename = upload_file.name
            f.file_name = filename
            if not os.path.exists('upload/'):
                os.mkdir('upload/')
            print filename
            filename = 'upload/' + filename
            f.save()
            with open(filename, 'wb+') as destination:
                for r in upload_file.chunks():
                    destination.write(r)
                destination.close()
            # print "=======================success================="
            return HttpResponseRedirect('/')
        except Exception, ex:
            print ex
            return JsonResponse({'code': 0, 'reason': u'导入数据失败'})



