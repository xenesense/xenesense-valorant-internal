
include ksamd64.inc

        subttl  "Check Stack"


        LEAF_ENTRY __chkstk, _TEXT$00

        ret                             ; return

        LEAF_END __chkstk, _TEXT$00

        end
