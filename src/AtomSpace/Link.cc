/**
 * Link.cc
 *
 * Copyright(c) 2001 Thiago Maia, Andre Senna
 * All rights reserved.
 */

#include "Link.h"
#include "ClassServer.h"
#include "StatisticsMonitor.h"
#include "exceptions.h"
#include "Node.h"
#include "TLB.h"
#include "utils.h"
#include "Trail.h"
#include "CoreUtils.h"
#include "AtomSpaceDefinitions.h"
#include "Logger.h"


void Link::init(void) throw (InvalidParamException)
{
    if (!ClassServer::isAssignableFrom(LINK, type)) {
#ifndef USE_STD_VECTOR_FOR_OUTGOING
        if (outgoing) free(outgoing);
#endif
        throw InvalidParamException(TRACE_INFO, "Link -  invalid link type: %d", type);
    }
    trail = new Trail();
}

Link::Link(Type type, const std::vector<Handle>& outgoingVector, const TruthValue& tv)
    : Atom(type, outgoingVector, tv)
{
    init();
}

Link::~Link() throw ()
{
    //printf("Link::~Link() begin\n");
//    fprintf(stdout, "Deleting link:\n%s\n", this->toString().c_str());
//    fflush(stdout);
    delete trail;
    //printf("Link::~Link() end\n");
}

void Link::setTrail(Trail* t)
{
    if (trail) {
        delete(trail);
    }
    trail = t;
}

Trail* Link::getTrail()
{
    return trail;
}

std::string Link::toShortString()
{
    std::string answer;
#define BUFSZ 1024
    char buf[BUFSZ];

    snprintf(buf, BUFSZ, "[%d %s", type, (getFlag(HYPOTETHICAL_FLAG)?"h ":""));
    answer += buf;
    // Here the targets string is made. If a target is a node, its name is
    // concatenated. If it's a link, all its properties are concatenated.
    answer += "<";
    for (int i = 0; i < getArity(); i++) {
        if (i > 0) answer += ",";
        answer += ClassServer::isAssignableFrom(NODE, TLB::getAtom(outgoing[i])->getType()) ?
                        ((Node*) TLB::getAtom(outgoing[i]))->getName() :
                        ((Link*) TLB::getAtom(outgoing[i]))->toShortString();
    }
    answer += ">";
    float mean = this->getTruthValue().getMean();
    float count = this->getTruthValue().getCount();
    snprintf(buf, BUFSZ, " %f %f", mean, count);
    answer += buf;
    answer += "]";
    return answer;
}

std::string Link::toString()
{
    std::string answer;
    char buf[BUFSZ];

    snprintf(buf, BUFSZ, "link[%d sti:(%d,%d) tv:(%f,%f) ", type,
       (int)getAttentionValue().getSTI(),
       (int)getAttentionValue().getLTI(),
       getTruthValue().getMean(),
       getTruthValue().getConfidence());
    answer += buf;
    // Here the targets string is made. If a target is a node, its name is
    // concatenated. If it's a link, all its properties are concatenated.
    answer += "<";
    for (int i = 0; i < getArity(); i++) {
        if (i > 0) answer += ",";
        Type t = TLB::getAtom(outgoing[i])->getType();
        //MAIN_LOGGER.log(Util::Logger::FINE, "toString() => type of outgoing[%d] = %d", i, t);
        if (ClassServer::isAssignableFrom(NODE, t)) {
            answer += ((Node*) TLB::getAtom(outgoing[i]))->getName();
        } else if  (ClassServer::isAssignableFrom(LINK, t)) {
            answer += ((Link*) TLB::getAtom(outgoing[i]))->toString();
        } else {
            MAIN_LOGGER.log(Util::Logger::ERROR, "Link::toString() => type of outgoing[%d] = %d is invalid", i, t);
            answer += "INVALID_ATOM_TYPE!";
        }
    }
    answer += ">]";
    return answer;
}

float Link::getWeight()
{
    return getTruthValue().toFloat();
}

bool Link::isSource(Handle handle) throw (InvalidParamException)
{
    // On ordered links, only the first position in the outgoing set is a source
    // of this link. So, if the handle given is equal to the first position,
    // true is returned.
    if (ClassServer::isAssignableFrom(ORDERED_LINK, type)) {
        return getArity() > 0 && outgoing[0] == handle;
    } else if (ClassServer::isAssignableFrom(UNORDERED_LINK, type)) {
        // if the links is unordered, the outgoing set is scanned, and the
        // method returns true if any position is equal to the handle given.
        for (int i = 0; i < getArity(); i++) {
            if (outgoing[i] == handle) {
                return true;
            }
        }
        return false;
    } else {
        throw InvalidParamException(TRACE_INFO, "Link::isSource(Handle) unknown link type %d", type);
    }
}

bool Link::isSource(int i) throw (IndexErrorException, InvalidParamException)
{
    // tests if the int given is valid.
    if ((i > getArity()) || (i < 0)) {
        throw IndexErrorException(TRACE_INFO, "Link::isSource(int) invalid index argument");
    }

    // on ordered links, only the first position in the outgoing set is a source
    // of this link. So, if the int passed is 0, true is returned.
    if (ClassServer::isAssignableFrom(ORDERED_LINK, type)) {
        return i == 0;
    } else if (ClassServer::isAssignableFrom(UNORDERED_LINK, type)) {
        // on unordered links, the only thing that matter is if the int passed
        // is valid (if it is within 0..arity).
        return true;
    } else {
        throw InvalidParamException(TRACE_INFO, "Link::isSource(int) unknown link type %d", type);
    }
}

bool Link::isTarget(Handle handle) throw (InvalidParamException)
{
    // on ordered links, the first position of the outgoing set defines the
    // source of the link. The other positions are targets. So, it scans the
    // outgoing set from the second position searching for the given handle. If
    // it is found, true is returned.
    if (ClassServer::isAssignableFrom(ORDERED_LINK, type)) {
        for (int i = 1; i < getArity(); i++) {
            if (outgoing[i] == handle) {
                return true;
            }
        }
        return false;
    } else if (ClassServer::isAssignableFrom(UNORDERED_LINK, type)) {
        // if the links is unordered, all the outgoing set is scanned.
        for (int i = 0; i < getArity(); i++) {
            if (outgoing[i] == handle) {
                return true;
            }
        }
        return false;
    } else {
        throw InvalidParamException(TRACE_INFO, "Link::isTarget(Handle) unknown link type %d", type);
    }
}

bool Link::isTarget(int i) throw (IndexErrorException, InvalidParamException)
{
    // tests if the int given is valid.
    if ((i > getArity()) || (i < 0)) {
        throw IndexErrorException(TRACE_INFO, "Link::istarget(int) invalid index argument");
    }

    // on ordered links, the first position of the outgoing set defines the
    // source of the link. The other positions are targets.
    if (ClassServer::isAssignableFrom(ORDERED_LINK, type)) {
        return i != 0;
    } else if (ClassServer::isAssignableFrom(UNORDERED_LINK, type)) {
        // on unorderd links, the only thing that matter is if the position is
        // valid.
        return true;
    } else {
        throw InvalidParamException(TRACE_INFO, "Link::isTarget(int) unkown link type");
    }
}

bool Link::equals(Atom* other)
{
    if (type != other->getType()) return false;

    Link *olink = dynamic_cast<Link *>(other);
    if (getArity() != olink->getArity()) return false;

    for (int i = 0; i < getArity(); i++){
        if (outgoing[i] != olink->outgoing[i]) return false;
    }

    return true;
}

int Link::hashCode(void)
{
    long result = type + (getArity()<<8);

    for (int i = 0; i < getArity(); i++){
        result = result  ^ (((long) outgoing[i])<<i);
    }
    return (int) result;
}

