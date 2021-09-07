
(cl:in-package :asdf)

(defsystem "fruit_couting_base-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :geometry_msgs-msg
               :std_msgs-msg
)
  :components ((:file "_package")
    (:file "vecPoints" :depends-on ("_package_vecPoints"))
    (:file "_package_vecPoints" :depends-on ("_package"))
  ))