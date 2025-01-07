#!/usr/bin/python3
# -----------------------------------------------------------------------------
#  The Python binding for Cyberiada GraphML library
# 
#  The empty document metainformation test
# 
#  Copyright (C) 2025 Alexey Fedoseev <aleksey@fedoseev.net>
# 
#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
# 
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
# 
#  You should have received a copy of the GNU General Public License
#  along with this program. If not, see https://www.gnu.org/licenses/
#  ----------------------------------------------------------------------------- 

import sys
import traceback
import CyberiadaML

try:
    d = CyberiadaML.LocalDocument()
    d.new_state_machine("SM", CyberiadaML.Rect())
    d.get_meta().platform_name = "Berloga"
    d.get_meta().platform_version = "1.4"
    d.get_meta().platform_language = "script"
    d.get_meta().target_system = "Unit"
    d.get_meta().name = "Test document"
    d.get_meta().author = "Author"
    d.get_meta().contact = "platform@kruzhok.org"
    d.get_meta().description = "1\n2\n3" 
    d.get_meta().version = "0.1"
    d.get_meta().date = "2024-04-14T11:22:00"
    d.get_meta().markup_language = "html"
    d.get_meta().transition_order_flag = True # exit first
    d.get_meta().event_propagation_flag = True # propagate
    d.save_as(sys.argv[0] + ".graphml", CyberiadaML.formatCyberiada10, False)
except Exception as e:
    print('Unexpected exception: {}'.format(e.__class__))
    print(traceback.format_exc())
    exit(1)

exit(0)
