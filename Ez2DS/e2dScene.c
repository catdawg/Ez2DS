#include "e2dScene.h"

#include <stdio.h>
#include <string.h> 
#include <ctype.h>
 
#include "mxml.h"
#include "e2dElement.h"
#include "e2dGroup.h"
#include "e2dImage.h"
#include "e2dPath.h"

static mxml_node_t *tree;


static e2dMatrix 
parseTransform(mxml_node_t* node)  {
    e2dMatrix matrix = E2D_IDENT_MATRIX;
    const char* transform = mxmlElementGetAttr(node, "transform");
    
    if(transform == E2D_NULL)//no transform attribute in this element
        return matrix;
    
    const char* values = strchr(transform, '(');
    if(values == E2D_NULL)
        return matrix; //TODO error
    values++;//remove '('
    
    char* val;
    
    //copy everything for use with strtok, plus 1 for \0
    char* values_copied = (char*)calloc(strlen(values) + 1, sizeof(char)); 
    memcpy(values_copied, values, strlen(values));

    //read the values and convert them to floats
    float f[6] = {0,0,0,0,0,0};
    unsigned int i = 0;
    val = strtok(values_copied, ",");
    while(val != E2D_NULL)
    {
        f[i] = (float)atof(val);
        val = strtok(E2D_NULL, ",");
        ++i;
    }
    free(values_copied);
    
    //read the type of transform
    char type_transform[20];
    sscanf(transform, "%[^'(']", type_transform);
    
    if(strcmp(type_transform, "matrix") == 0)
    {
        e2dMatrixSetCol(&matrix, 0, f[0],     f[1], 0);
        e2dMatrixSetCol(&matrix, 1, f[2],     f[3], 0);
        e2dMatrixSetCol(&matrix, 2, f[4],     f[5], 1);
    }else
    {
        if(strcmp(type_transform, "translate") == 0)
        {
            e2dMatrixSetCol(&matrix, 2, f[0],     f[1], 1);
        }else
        {
            if(strcmp(type_transform, "scale") == 0)
            {
                e2dMatrixSetCell(&matrix, 0, 0, f[0]);
                e2dMatrixSetCell(&matrix, 1, 1, f[1]);
            }
        }
    }
    return matrix;    
    
}

static void 
parseAttributes(mxml_node_t* node, e2dElement* elem)  {
    int i;
    for(i = 0; i < node->value.element.num_attrs; ++i)
    {
        e2dElementAddAttribute(elem, node->value.element.attrs[i].name, 
                node->value.element.attrs[i].value);
    }
}

static 
e2dImage* parseImage(mxml_node_t* node, e2dScene* scene)  {
    e2dImage* image = e2dImageCreate(scene);
    //parse transformation
    image->element.localTransform = parseTransform(node);
    
    //parse attributes
    parseAttributes(node, (e2dElement*)image);
    
    const char* value = mxmlElementGetAttr(node, "x");
    if(value != NULL)
        image->position.x = (float)atof(value);
    
    value = mxmlElementGetAttr(node, "y");
    if(value != NULL)
        image->position.y = (float)atof(value);
    
    value = mxmlElementGetAttr(node, "width");
    if(value != NULL)
        image->width = (float)atof(value);
    
    value = mxmlElementGetAttr(node, "height");
    if(value != NULL)
        image->height = (float)atof(value);
   
    value = mxmlElementGetAttr(node, "xlink:href");
    if(value != NULL)
    {
        image->imagePath = (char*)malloc(sizeof(char)*strlen(value) + 1);
        strcpy(image->imagePath, value);
    }
    return image;
}

static float
parseNumber(const char** points)  {
    
    while(*points && **points == ' ')
        ++points;
    
    const char* points_aux = *points;
    while(*points_aux && *points_aux != ' ' && *points_aux != ',') ++points_aux;
    
    points_aux++;
    
    float num = (float)atof(*points);
    *points = points_aux;
    return num;
}

static e2dPoint
parsePoint(const char** points)  {
    e2dPoint p;
    
    p.x = parseNumber(points);
    p.y = parseNumber(points);
    
    return p;
}

static void 
parseVerticalTo(e2dPath* path, const char** points, e2dPoint* currentPoint,
        E2D_BOOL relative)  {
    while(E2D_TRUE) {   
        while(**points && **points == ' ')
            ++*points;
        
        //check if we reached another command
        while(**points && (!isalnum(**points) || **points == '-')) ++*points;
        
        if(!**points)
            return;
        
        
        if(isdigit(**points) || **points == '-')  {
            e2dPoint p = *currentPoint;
            if(relative)
                p.y += parseNumber(points);
            else
                p.y = parseNumber(points);
            
            e2dPathPoint* pathPoint = e2dPathPointCreate();
            pathPoint->point = p;
            *currentPoint = pathPoint->point;
            
            e2dPathAddPathElement(path, (e2dPathElement*)pathPoint);
            continue;
        }
        return;
        
    }
    
}

static void 
parseHorizontalTo(e2dPath* path, const char** points, e2dPoint* currentPoint,
        E2D_BOOL relative)  {
    
    while(E2D_TRUE) {   
        while(**points && **points == ' ')
            ++*points;
        
        //check if we reached another command
        while(**points && (!isalnum(**points) || **points == '-')) ++*points;
        
        if(!**points)
            return;
        
        
        if(isdigit(**points) || **points == '-')  {
            e2dPoint p = *currentPoint;
            if(relative)
                p.x += parseNumber(points);
            else
                p.x = parseNumber(points);
            
            e2dPathPoint* pathPoint = e2dPathPointCreate();
            pathPoint->point = p;
            *currentPoint = pathPoint->point;
            
            e2dPathAddPathElement(path, (e2dPathElement*)pathPoint);
            continue;
        }
        return;
        
    }
    
}

static void 
parseLineTo(e2dPath* path, const char** points, e2dPoint* currentPoint,
        E2D_BOOL relative)  {
    
    while(**points)  {
        while(**points && **points == ' ')
            ++*points;
        
        //check if we reached another command
        while(!**points && !isalnum(**points) && **points != '-') ++*points;
        
        if(!**points)
            return;
        
        if(isdigit(**points) || **points == '-')  {
            e2dPoint p = parsePoint(points);
            

            if(relative)
            {
                p.x += (*currentPoint).x;
                p.y += (*currentPoint).y;
            }
            e2dPathPoint* pathPoint = e2dPathPointCreate();
            pathPoint->point = p;
            *currentPoint = pathPoint->point;
            
            e2dPathAddPathElement(path, (e2dPathElement*)pathPoint);
            continue;
        }
        return;
    }
}

static e2dPoint
getPrevious2ndControlPoint(e2dPath* path, e2dPoint* currentPoint)  {
    
    if(path->pathElementsNum > 0 && 
       path->pathElements[path->pathElementsNum - 1]->type == E2D_PATHCURVE)
        return 
            ((e2dPathCurve*)path->pathElements[path->pathElementsNum - 1])
                ->controlPoint2;
    else
        return *currentPoint;
    
}

static void 
parseCurveTo(e2dPath* path, const char** points, e2dPoint* currentPoint,
        E2D_BOOL relative, E2D_BOOL smooth)  {
    
    while(**points)  {
        while(**points && **points == ' ')
            ++*points;
        
        //check if we reached another command
        while(**points && !(isalnum(**points) || **points == '-')) ++*points;
        
        if(!**points)
            return;
        
        if(isdigit(**points) || **points == '-')
        {
            
            e2dPoint c1, c2;
            
            if(smooth)  {
                e2dPoint prev2ndControlPoint = 
                        getPrevious2ndControlPoint(path, currentPoint);
                c1.x = 2*currentPoint->x - prev2ndControlPoint.x;
                c1.y = 2*currentPoint->y - prev2ndControlPoint.y;
                
                c2 = parsePoint(points);
            }
            else  {
                c1 = parsePoint(points);
                c2 = parsePoint(points);
            }
            e2dPoint p = parsePoint(points);
            

            if(relative)  {
                p.x += (*currentPoint).x;
                p.y += (*currentPoint).y;
                c1.x += (*currentPoint).x;
                c1.y += (*currentPoint).y;
                c2.x += (*currentPoint).x;
                c2.y += (*currentPoint).y;
            }
            e2dPathCurve* pathCurve = e2dPathCurveCreate();
            pathCurve->startPoint = *currentPoint;
            pathCurve->endPoint = p;
            pathCurve->controlPoint1 = c1;
            pathCurve->controlPoint2 = c2;
            *currentPoint = pathCurve->endPoint;
            
            e2dPathAddPathElement(path, (e2dPathElement*)pathCurve);
            continue;
        }
        return;
    }
    
}

static void 
parseMoveTo(e2dPath* path, const char** points, e2dPoint* currentPoint,
        E2D_BOOL relative, E2D_BOOL first)  {
    
    while(**points && **points == ' ')
        ++*points;
    
    
    //if it is the first, then the first coords are absolute, else they are whatever relative says.
    E2D_BOOL relative2 =  first ? E2D_FALSE : relative;
    e2dPoint p = parsePoint(points);
    
    if(relative2)
    {
        p.x += (*currentPoint).x;
        p.y += (*currentPoint).y;
    }
    e2dPathPoint* pathPoint = e2dPathPointCreate();
    pathPoint->point = p;
    pathPoint->element.controlType = E2D_START_SUBPATH;
    *currentPoint = pathPoint->point;
    
    e2dPathAddPathElement(path, (e2dPathElement*)pathPoint);
}

static void 
parsePathElements(e2dPath* path, const char* points)  {
    
    e2dPoint currentPoint;
    e2dPoint currentSubPathStartPoint;
    
    
    //ignore first offending spaces
    while(*points && *points == ' ')
        ++points;
    
    //check the first command (should be move-to)
    if(*points != 'M' && *points != 'm')  {
        //TODO error
        return;
    }
    
    //boolean indicating if the current coords are relative or not
    E2D_BOOL relative = E2D_FALSE;
    
    //check if the move-to is lower or not
    relative = !isupper(*points);
    
    //remove the command
    points++;
    //go parse the first move-to, it's different because the first coord is 
    //always absolute so we need that boolean in the end
    parseMoveTo(path, &points, &currentPoint, relative, E2D_TRUE);
    
    currentSubPathStartPoint = currentPoint;
    
    parseLineTo(path, &points, &currentPoint, relative);
    
    
    while(*points && !isalnum(*points)) ++points;
    
    
    //while we don't reach the end of the string or the ending command is found
    while(*points && points && *points != 'z' && *points != 'Z')
    {
        //get the next command (we might already be there if it's the first)
        while(*points && !isalnum(*points)) ++points;
    
        //a move-to command
        if(*points == 'm' || *points == 'M')
        {
            if(path->pathElementsNum > 0 && 
                    path->pathElements[path->pathElementsNum - 1]->controlType
                == E2D_NOCONTROL)
                path->pathElements[path->pathElementsNum - 1]->controlType =
                        E2D_END_SUBPATH;
            
            relative = !isupper(*points);
            //remove the command
            points++;
            parseMoveTo(path, &points, &currentPoint, relative, E2D_FALSE);
            
            currentSubPathStartPoint = currentPoint;
            
            parseLineTo(path, &points, &currentPoint, relative);
            continue;
        }
        
        //a line-to command
        if(*points == 'l' || *points == 'L')
        {
            relative = !isupper(*points);
            //remove the command
            points++;
            parseLineTo(path, &points, &currentPoint, relative);
            continue;
        }
        
        //an horizontal-to command
        if(*points == 'h' || *points == 'H')
        {
            relative = !isupper(*points);
            //remove the command
            points++;
            parseHorizontalTo(path, &points, &currentPoint, relative);
            continue;
        }
        
        //a vertical-to command
        if(*points == 'v' || *points == 'V')
        {
            relative = !isupper(*points);
            //remove the command
            points++;
            parseVerticalTo(path, &points, &currentPoint, relative);
            continue;
        }
        
        //a curve-to command
        if(*points == 'c' || *points == 'C')
        {
            relative = !isupper(*points);
            //remove the command
            points++;
            parseCurveTo(path, &points, &currentPoint, relative, E2D_FALSE);
            
            continue;
        }
        
        //a curve-to command
        if(*points == 's' || *points == 'S')
        {
            relative = !isupper(*points);
            //remove the command
            points++;
            parseCurveTo(path, &points, &currentPoint, relative, E2D_TRUE);
            continue;
        }
        
        //an end path command
        if(*points == 'z' || *points == 'Z')
        {
            if(path->pathElementsNum > 0)
                path->pathElements[path->pathElementsNum - 1]->controlType =
                        E2D_END_SUBPATH_LOOP;
            currentPoint = currentSubPathStartPoint;
            
            //remove the command
            points++;
            continue;
        }
        
       
        if(isalpha(*points))
        {
            //TODO ERROR
            break;
        }
            
    }
        
        if(path->pathElements[path->pathElementsNum - 1]->controlType 
                == E2D_NOCONTROL)
           path->pathElements[path->pathElementsNum - 1]->controlType =
                   E2D_END_SUBPATH;
            
    
    
}

static e2dPath* 
parsePath(mxml_node_t* node, e2dScene* scene)  {
    e2dPath* path = e2dPathCreate(scene);
    //parse transformation
    path->element.localTransform = parseTransform(node);
    
    
    const char* points = mxmlElementGetAttr(node, "d");
    if(points != NULL)
        parsePathElements(path, points);
    
    return path;
}

static e2dGroup* 
parseGroup(mxml_node_t* node, e2dScene* scene);

static void 
parseChildElements(mxml_node_t* node, e2dScene* scene, e2dGroup* parent) {
    mxml_node_t* current = mxmlGetFirstChild(node); 
    const char* currentName;
    while(current != NULL)  {
        currentName = mxmlGetElement(current);
        if(currentName == NULL)
        {
            current = mxmlGetNextSibling(current);
            continue;
        }
            
        if(strcmp("g", currentName) == 0)
            e2dGroupAddChild(parent, (e2dElement*)parseGroup(current, scene));
        else
        {
            if(strcmp("image", currentName) == 0)
                e2dGroupAddChild(parent, (e2dElement*)parseImage(current, scene));
            else if(strcmp("path", currentName) == 0)
                e2dGroupAddChild(parent, (e2dElement*)parsePath(current, scene));
        }
        
        current = mxmlGetNextSibling(current);
        
        
    }
}

static e2dGroup* 
parseGroup(mxml_node_t* node, e2dScene* scene)  {
    e2dGroup* group = e2dGroupCreate(scene); 
    //parse transformation
    group->element.localTransform = parseTransform(node);
    //parse attributes
    parseAttributes(node, (e2dElement*)group);
    
    //find the rect for bounding box
    mxml_node_t* rect = mxmlFindElement(node, tree, "rect",
                        E2D_NULL, E2D_NULL,
                        MXML_DESCEND_FIRST);
    if(rect != E2D_NULL)
    {
        const char* value = mxmlElementGetAttr(node, "x");
        if(value != NULL)
            group->element.bboxPosition.x = (float)atof(value);

        value = mxmlElementGetAttr(node, "y");
        if(value != NULL)
            group->element.bboxPosition.y = (float)atof(value);

        value = mxmlElementGetAttr(node, "width");
        if(value != NULL)
            group->element.bboxWidth = (float)atof(value);

        value = mxmlElementGetAttr(node, "height");
        if(value != NULL)
            group->element.bboxHeight = (float)atof(value);
    }
    parseChildElements(node, scene, group);
    return group;
}



e2dScene* 
createSceneFromFile(char* file)  {
    FILE *fp;
    fp = fopen(file, "r");
    tree = mxmlLoadFile(NULL, fp,
                        MXML_TEXT_CALLBACK);
    
    mxml_node_t *start_elem;
    
    start_elem = mxmlFindElement(tree, tree, "svg", NULL, NULL, MXML_DESCEND);
    
    if(start_elem == E2D_NULL)
        return E2D_NULL; //TODO error
    
    
    e2dScene* scene = (e2dScene*)malloc(sizeof(e2dScene));
    
    scene->root = e2dGroupCreate(scene);
    
    parseChildElements(start_elem, scene, scene->root);
    
    fclose(fp);
    
    e2dSceneCalculateEffectiveTransforms(scene);
    return scene;
}

void 
_e2dSceneCalculateEffectiveTransforms(e2dGroup* group)  {
    if(group->element.parent == 0)
    {
        ((e2dElement*)group)->effectiveTransform = 
                ((e2dElement*)group)->localTransform;
        
    }   
    else
    {
        ((e2dElement*)group)->effectiveTransform = e2dMatrixMultiply(
                &(((e2dElement*)group->element.parent)->effectiveTransform), 
                &(((e2dElement*)group)->localTransform));
    }
        
    e2dGroupIterator iter = e2dGroupGetChildIterator(group);
    e2dElement* elem;
    while(e2dGroupIteratorHasNext(&iter))  {
        elem = e2dGroupIteratorNext(&iter);
        if(elem->type == E2D_GROUP)
        {
            _e2dSceneCalculateEffectiveTransforms((e2dGroup*)elem);
        }
        else
        {
            elem->effectiveTransform = e2dMatrixMultiply(
                &(((e2dElement*)group)->effectiveTransform), 
                &(elem->localTransform));
            
            elem->inverseEffectiveTransform = 
                    e2dMatrixGetInverse(&(elem->effectiveTransform));
        }
    }
    
    ((e2dElement*)group)->inverseEffectiveTransform = 
            e2dMatrixGetInverse(&(((e2dElement*)group)->effectiveTransform));
}

void
e2dSceneCalculateEffectiveTransforms(e2dScene* scene)
{
    _e2dSceneCalculateEffectiveTransforms(scene->root);
}



void
_recursivelyCenterGroupAtBBox(e2dGroup* group, float tx, float ty)  {
    e2dGroupIterator iter = e2dGroupGetChildIterator(group);
    e2dElement* elem;
    while(e2dGroupIteratorHasNext(&iter))  {
        elem = e2dGroupIteratorNext(&iter);
        e2dElementCenterAtBBox(elem, tx, ty);
        if(elem->type == E2D_GROUP)
            _recursivelyCenterGroupAtBBox((e2dGroup*)elem, 
                    tx, ty);
        
    }
}

void
e2dSceneCenterAllAtBBox(e2dScene* scene, float tx, float ty)  {
     e2dGroupCenterAtBBox(scene->root, tx, ty);
     _recursivelyCenterGroupAtBBox(scene->root, 
                    tx, ty);
}


void
e2dSceneCalculateAllBBox(e2dScene* scene)  {
     e2dGroupCalculateBoundingBox(scene->root);
}
