;;
;; Configuration file for the example crisp rule base system (used by
;; fc-deduction.scm)
;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Load required modules and utils ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(use-modules (opencog))
(use-modules (opencog ure))

;; Useful to run the unit tests without having to install opencog
(load-from-path "ure-utils.scm")

;;;;;;;;;;;;;;;;
;; Load rules ;;
;;;;;;;;;;;;;;;;
(load-from-path "tests/ure/rules/fc-deduction-rule.scm")

;; Define a new rule base (aka rule-based system)
(define fc-deduction-rbs (ConceptNode "fc-deduction-rule-base"))

;; Associate the rules to the rule base (with weights, their semantics
;; is currently undefined, we might settled with probabilities but it's
;; not sure)
(ure-add-rules fc-deduction-rbs (list fc-deduction-rule-name))

;; Termination criteria parameters
(ure-set-maximum-iterations fc-deduction-rbs 20)
