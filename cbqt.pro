TEMPLATE = subdirs
SUBDIRS = cbsupport cbsource cbserver/CBServerMonitor

cbsource.depends = cbsupport
cbserver/CBServerMonitor.depends = cbsupport cbsource
