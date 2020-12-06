//
//  DataFileManager.hpp
//  Shelly Switcher WatchKit Extension
//
//  Created by Arthur Freda on 12/4/20.
//

#ifndef DataFileManager_hpp
#define DataFileManager_hpp

#include <stdio.h>
#include "ShellyItem.hpp"

extern ShellyItem *shellyList;
extern ShellyItem *currentShelly;

void LoadSettings();
void SaveSettings();

#endif /* DataFileManager_hpp */
