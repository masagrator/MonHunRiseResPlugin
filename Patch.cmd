@echo off
nsnsotool 0100B04011742000\exefs\subsdk9 0100B04011742000\exefs\subsdk9_unc
python MHRiseResolution.py
nsnsotool 0100B04011742000\exefs\subsdk9_unc 0100B04011742000\exefs\subsdk9
del 0100B04011742000\exefs\subsdk9_unc
pause