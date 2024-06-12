//======= Copyright (c) 2024, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Test Driven Development - graph
//
// $NoKeywords: $ivs_project_1 $tdd_code.cpp
// $Author:     Patrik Mokruša <xmokrup00@stud.fit.vutbr.cz>
// $Date:       $2024-02-14
//============================================================================//
/**
 * @file tdd_code.cpp
 * @author Martin Dočekal
 * @author Karel Ondřej
 *
 * @brief Implementace metod tridy reprezentujici graf.
 */

#include "tdd_code.h"


Graph::Graph(){}

Graph::~Graph(){}

std::vector<Node*> Graph::nodes() {
    // Graph::graph_nodes;
    std::vector<Node*> nodes;
    int i=0;
    for(Node node : nodes_array){
        nodes.push_back(&nodes_array[i]);
        i++;
    }

    return nodes;
}

std::vector<Edge> Graph::edges() const{
    // std::vector<Edge> edges;
    

    return edges_array;
}

Node* Graph::addNode(size_t nodeId) {
    // auto nodes = Graph::graph_nodes;

    Node new_node;
    new_node.id = nodeId;
    new_node.color = 0;

    for (auto node : nodes_array){
        if (node.id == new_node.id){
            return nullptr;
        }
    }

    nodes_array.push_back(new_node);
    return &nodes_array.back();
}

bool Graph::addEdge(const Edge& edge){

    if (edge.a == edge.b)
    {
        return false;
    }

    for (auto temp_edge : edges_array){
        if(temp_edge == edge){
            return false;
        }
    }
    
    edges_array.push_back(edge);

    return true;
    // return false;

}

void Graph::addMultipleEdges(const std::vector<Edge>& edges) {
    for (Edge new_edge : edges)
    {
        if (true == addEdge(new_edge)){
            addNode(new_edge.a);
            addNode(new_edge.b);
        }
        
        // if (true == addEdge(new_edge)){
        //     int counter =0;
        //     for (auto node : nodes_array){
        //         if ((new_edge.a || new_edge.b) == node.id){
        //             counter++;
        //         }
        //     }
            
        // }
    }
    

}

Node* Graph::getNode(size_t nodeId){
    int i = 0;
    for (auto node : nodes_array){
        if (node.id == nodeId){
            return &nodes_array[i];
        }
        i++;
    }

    return nullptr;
}

bool Graph::containsEdge(const Edge& edge) const{

    for (auto temp_edge : edges_array){
        if ((temp_edge == edge) || ((temp_edge.a == edge.b)&&(temp_edge.b == edge.a))){
            return true;
        }
    }

    return false;
}

void Graph::removeNode(size_t nodeId){
    int i = 0;
    for (auto node : nodes_array){
        if (node.id == nodeId){
            std::swap(nodes_array.back(), nodes_array[i]);
            nodes_array.shrink_to_fit();
            nodes_array.pop_back();

            // int j = 0;
            // for (auto edge : edges_array){
            //     if ((edge.a == nodeId)||(edge.b == node.id)){
            //         removeEdge(edges_array[j]);
            //     }
            //     j++;
            // }
            int size = edges_array.size();
            for (int j = 0; j < size; j++)
            {
                if ((edges_array[j].a == nodeId)||(edges_array[j].b == nodeId)){
                    removeEdge(edges_array[j]);
                    size = size -1;
                    j=0;
                }
            }
            
            return;
        }
        i++;
    }
    throw std::out_of_range("brikulosakosovic");
    
    
}

void Graph::removeEdge(const Edge& edge){
    int i = 0;
    for (auto temp_edge : edges_array){
        if (temp_edge == edge){
            std::swap(edges_array.back(), edges_array[i]);
            edges_array.shrink_to_fit();
            edges_array.pop_back();
            return;
        }
        i++;
    }

    throw std::out_of_range("");
}

size_t Graph::nodeCount() const{
    
    
    return nodes_array.size();
}

size_t Graph::edgeCount() const{
    
    return edges_array.size();
}

size_t Graph::nodeDegree(size_t nodeId) const{
    size_t counter = 0;
    for (auto edge : edges_array){
        if ((edge.a == nodeId)||(edge.b == nodeId)){
            counter++;
        }
    }

    if(counter == 0)
        throw std::out_of_range("Degree = 0  or not even in graph");

    return counter;
}

size_t Graph::graphDegree() const{
    size_t max_node_degree = 0;
    size_t temp_degree = 0;
    
    for (auto temp_node : nodes_array){
        temp_degree = nodeDegree(temp_node.id);
        if (temp_degree > max_node_degree){
            max_node_degree = temp_degree;
        }
    }
    return max_node_degree;
}

void Graph::coloring(){
    int color = 1;
    for (int i = 0; i < nodes_array.size(); i++)
    {
        nodes_array[i].color = color;
        color++;
    }
    
}

void Graph::clear() {
    nodes_array.clear();
    edges_array.clear();
}

std::vector<size_t>* Graph::create_adj_list() {


    size_t max_id = 0;
    for (auto temp_node : nodes_array){
        if (temp_node.id > max_id){
            max_id = temp_node.id;
        }
    }
    
    std::vector<size_t> adj_list[max_id +1];


    for (auto temp_edge : edges_array){
        adj_list[temp_edge.a].push_back(temp_edge.b);
        adj_list[temp_edge.b].push_back(temp_edge.a);
    }

    std::vector<size_t> *ptr = (std::vector<size_t>*)malloc(sizeof(adj_list));
    if (ptr == nullptr){
        return nullptr;
    }

    ptr = adj_list;

    // for (size_t i = 0; i < (max_id); i++)
    // {
    //     ptr[i] = adj_list[i];
    // }
    

    return ptr;
}

void Graph::adj_list_dtor(std::vector<size_t>* ptr){
    
    free(ptr);
}

/*** Konec souboru tdd_code.cpp ***/
