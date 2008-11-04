scm
;
; type-definitions.scm
;
; A set of type definitions that hold for some of the more "obscure"
; RelEx types. These are "anti-syntactic sugar", and avoid the need
; for new atom types, such as "GenderNode" or "TenseNode", etc.
;
; Copyright (c) 2008 Linas Vepstas
;
; XXX This list is *probably* incomplete, and needs to be reviewed! XXX
; In particular, the tense list is incomplete. The par-of-speech list 
; might be incomplete.
; The list of inflections is incomplete.
; The list of entities (person, locatin, date, money) is incomplete.
; The place to check for completeness is on the RelEx wiki page,
; documenting these things. See
; http://opencog.org/wiki/RelEx_Semantic_Relationship_Extractor
; 
; In alphabetic order.
;
;; -------------------------------------------------------------------
; DEFINITE-FLAG in RelEx
(InheritanceLink
	(DefinedLinguisticConceptNode "definite")
	(ConceptNode "DefinedLinguisticConcept-Determiner")
)

;; -------------------------------------------------------------------
; gender in RelEx
;
(InheritanceLink
	(DefinedLinguisticConceptNode "feminine")
	(ConceptNode "DefinedLinguisticConcept-Gender")
)

(InheritanceLink
	(DefinedLinguisticConceptNode "masculine")
	(ConceptNode "DefinedLinguisticConcept-Gender")
)

(InheritanceLink
	(DefinedLinguisticConceptNode "neuter")
	(ConceptNode "DefinedLinguisticConcept-Gender")
)

;; -------------------------------------------------------------------
; HYP in RelEx
;
(InheritanceLink
	(DefinedLinguisticConceptNode "hyp")
	(ConceptNode "DefinedLinguisticConcept-Hypothetical")
)

;; -------------------------------------------------------------------
; inflection-TAG in RelEx
;
; XXX these should probably be replaced by a new InflectionNode,
; as there will likely be a lot of these, too many to list ? XXX
(InheritanceLink
	(DefinedLinguisticConceptNode ".a")
	(ConceptNode "DefinedLinguisticConcept-Inflection")
)

(InheritanceLink
	(DefinedLinguisticConceptNode ".f")
	(ConceptNode "DefinedLinguisticConcept-Inflection")
)

(InheritanceLink
	(DefinedLinguisticConceptNode ".g")
	(ConceptNode "DefinedLinguisticConcept-Inflection")
)

(InheritanceLink
	(DefinedLinguisticConceptNode ".n")
	(ConceptNode "DefinedLinguisticConcept-Inflection")
)

(InheritanceLink
	(DefinedLinguisticConceptNode ".v")
	(ConceptNode "DefinedLinguisticConcept-Inflection")
)

;; -------------------------------------------------------------------
; noun_number in RelEx
(InheritanceLink
	(DefinedLinguisticConceptNode "plural")
	(ConceptNode "DefinedLinguisticConcept-NounNumber")
)

(InheritanceLink
	(DefinedLinguisticConceptNode "singular")
	(ConceptNode "DefinedLinguisticConcept-NounNumber")
)

;; -------------------------------------------------------------------
; Part-of-speech
(InheritanceLink
	(DefinedLinguisticConceptNode "det")
	(ConceptNode "DefinedLinguisticConcept-PartOfSpeech")
)

(InheritanceLink
	(DefinedLinguisticConceptNode "noun")
	(ConceptNode "DefinedLinguisticConcept-PartOfSpeech")
)

(InheritanceLink
	(DefinedLinguisticConceptNode "prep")
	(ConceptNode "DefinedLinguisticConcept-PartOfSpeech")
)

(InheritanceLink
	(DefinedLinguisticConceptNode "punctuation")
	(ConceptNode "DefinedLinguisticConcept-PartOfSpeech")
)

(InheritanceLink
	(DefinedLinguisticConceptNode "verb")
	(ConceptNode "DefinedLinguisticConcept-PartOfSpeech")
)

(InheritanceLink
	(DefinedLinguisticConceptNode "WORD")
	(ConceptNode "DefinedLinguisticConcept-PartOfSpeech")
)

;; -------------------------------------------------------------------
; person-FLAG in RelEx
(InheritanceLink
	(DefinedLinguisticConceptNode "person")
	(ConceptNode "DefinedLinguisticConcept-Person")
)

;; -------------------------------------------------------------------
; PRONOUN-FLAG in RelEx
(InheritanceLink
	(DefinedLinguisticConceptNode "pronoun")
	(ConceptNode "DefinedLinguisticConcept-Pronoun")
)

;; -------------------------------------------------------------------
; tense in RelEx
; XXX this list is highly incomplete
;
(InheritanceLink
	(DefinedLinguisticConceptNode "past")
	(ConceptNode "DefinedLinguisticConcept-Tense")
)

(InheritanceLink
	(DefinedLinguisticConceptNode "present")
	(ConceptNode "DefinedLinguisticConcept-Tense")
)

(InheritanceLink
	(DefinedLinguisticConceptNode "progressive")
	(ConceptNode "DefinedLinguisticConcept-Tense")
)

.
exit
