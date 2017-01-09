"""PeronsalWeb URL Configuration

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
from django.conf.urls import url
from django.contrib import admin
import os
from settings import STATICFILES_DIRS, BASE_DIR

from personal import views as pvs
from django import views as dvs

urlpatterns = [
    url(r'^admin/', admin.site.urls),
    url(r'^$', pvs.index),
    url(r'^upload/$', pvs.upload),
    url(r'^download/(?P<path>.*)$', dvs.static.serve, {'document_root': os.path.join(BASE_DIR, 'upload'), 'show_indexes': True}),
]
