WIN_BUILD_SCRIPTS_LOC = build_scripts_windows\\

all: main

main:
	$(WIN_BUILD_SCRIPTS_LOC)build.bat

launch:#default to windows
	$(WIN_BUILD_SCRIPTS_LOC)build_run.bat

run:#default to windows
	$(WIN_BUILD_SCRIPTS_LOC)run.bat

clean:#default to windows
	$(WIN_BUILD_SCRIPTS_LOC)clean.bat

win_launch:
	$(WIN_BUILD_SCRIPTS_LOC)build_run.bat

win_run:
	$(WIN_BUILD_SCRIPTS_LOC)run.bat

win_clean:
	$(WIN_BUILD_SCRIPTS_LOC)clean.bat
