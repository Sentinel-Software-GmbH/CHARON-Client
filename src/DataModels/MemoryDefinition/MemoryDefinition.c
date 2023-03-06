/*
 *  Sentinel Software GmbH
 *  Copyright (C) 2020 Steven Inácio
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 * 
 * Created on: Mon Aug 24 2020
 */
/**
 * @addtogroup UDS_Client
 * @{
 * @addtogroup DataModels Data Model Modules
 * @{
 * @file
 * Provides helper functions for MemoryDefinition.
 *
 * $Id:  $
 * $URL:  $
 * @}
 * @}
 */
/*****************************************************************************/

#include "MemoryDefinition.h"
#include <stdint.h>

uint8_t MemoryDefinition_getAddressAndLengthFormatIdentifier(MemoryDefinition * memdef) {
    return ((memdef->SizeLength & 0x0F) << 4) | (memdef->AddressLength & 0x0F);
}

