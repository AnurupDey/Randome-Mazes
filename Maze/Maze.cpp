/******************************************************************************
File		:	Maze.cpp
Author	:	Anurup Dey

				Copyright (C) 2015  Anurup Dey

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License along
	with this program; if not, write to the Free Software Foundation, Inc.,
	51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#include "Maze.h"
#include <cstdlib>
#include <ctime>

Maze::Maze(){
	m_size = 6;
	srand((unsigned)time(0));
}

bool Maze::edge_condition(position p){
	if (p%m_size == 0 || p%m_size == (m_size - 1) || 
		 p / m_size == 0 || p / m_size == (m_size - 1)   )
		return true;
	else return false;
}

void Maze::Generate(unsigned size){
	m_size = size;
	srand((unsigned)time(0));
	m_wall_list.clear();
	data.clear();
	//black out whole maze.
	for (unsigned i = 0; i < (m_size*m_size); ++i)
		data.push_back(BLACK_SPACE);

	

	//add first wall and space
	data[at_(1, (m_size - 1))] = SPACE;
	AddWall(at_(1, (m_size - 2)));

	while (m_wall_list.size() != 0){
		unsigned wall_index = (m_wall_list.size() == 1)? 0:rand() % (m_wall_list.size()-1);
		position wall_pos = m_wall_list[wall_index];
		position opp_side = get_opp_side(wall_pos);
		if (opp_side == 0){
			m_wall_list.erase(m_wall_list.begin() + wall_index);
			continue;
		}
		if (data[opp_side] == BLACK_SPACE && !In_wall_list(opp_side)){
			data[wall_pos] = SPACE;
			m_wall_list.erase(m_wall_list.begin() + wall_index);
			AddSpace(opp_side);
			if (data[opp_side] == SPACE){
				AddWall(opp_side + 1); AddWall(opp_side - 1);
				AddWall(opp_side + m_size); AddWall(opp_side - m_size);
			}
		}
		else m_wall_list.erase(m_wall_list.begin() + wall_index);
	}
	AddExit();
}

bool Maze::In_wall_list(position place){
	for (position wall : m_wall_list)
		if (wall == place) return true;
	return false;
}

void Maze::AddSpace(position place){
	if (!edge_condition(place)) data[place] = SPACE;
}

void Maze::AddWall(position place){
	if (!edge_condition(place) && !In_wall_list(place) && data[place] != SPACE)
		m_wall_list.push_back(place);
}

position Maze::get_opp_side(position p){
	if (!edge_condition(p)){
		if (data[p + 1] == SPACE) return p - 1;
		if (data[p - 1] == SPACE) return p + 1;
		if (data[p + m_size] == SPACE) return p - m_size;
		if (data[p - m_size] == SPACE) return p + m_size;
	}
	return 0;
}

void Maze::AddExit(){
	for (position p = at_((m_size-1),1); p <= at_((m_size-1),(m_size-2)); p += m_size){
		if (data[p - 1] == SPACE){
			data[p] = SPACE;
			exit = p;
			return;
		}
	}
}