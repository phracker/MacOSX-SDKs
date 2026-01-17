#----------------------------------------------------------------------------
# Add the directory where the wxWidgets catalogs were installed
# to the default catalog path, if they were put in the pacakge dir.
import os
_localedir = os.path.join(os.path.dirname(__file__), "locale")
if os.path.exists(_localedir):
    Locale.AddCatalogLookupPathPrefix(_localedir)
del os

#----------------------------------------------------------------------------
